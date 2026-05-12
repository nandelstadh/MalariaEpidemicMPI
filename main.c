#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prop.h"
#include "utils.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    if (argc != 2) {
        printf("Expected: main n\n");
        return -1;
    }
    int n = atoi(argv[1]);
    int n_procs, myid;
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)(myid * 0x9e3779b9u);
    srand(seed);
    const int P[15][7] = {
        {1, 0, 0, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0},
        {-1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, -1, 0, 0, 0, 0, 0},
        {0, -1, 0, 1, 0, 0, 0},
        {0, 0, -1, 0, 0, 0, 0},
        {0, 0, -1, 0, 1, 0, 0},
        {0, 0, 0, -1, 0, 0, 0},
        {0, 0, 0, -1, 0, 1, 0},
        {0, 0, 0, 0, -1, 0, 0},
        {0, 0, 0, 0, -1, 0, 1},
        {0, 0, 0, 0, 0, -1, 0},
        {1, 0, 0, 0, 0, 0, -1},
        {0, 0, 0, 0, 0, 0, -1}};
    const int T = 100;
    int (*X)[7] = malloc(sizeof(*X) * n);
    double w[15];
    double t = 0;
    int hist[NUM_BUCKETS];
    int gmax, gmin;

    double start = MPI_Wtime();
    for (int i = 0; i < n; i++) {
        X[i][0] = 900;
        X[i][1] = 900;
        X[i][2] = 30;
        X[i][3] = 330;
        X[i][4] = 50;
        X[i][5] = 270;
        X[i][6] = 20;

        t = 0;
        while (t < T) {
            t += gillespie(X[i], w, P);
        }
    }

    histogram(n, X, hist, &gmax, &gmin);
    double time = MPI_Wtime() - start;
    double maxtime;
    MPI_Reduce(&time, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (myid == 0) {
        printf("Time: %f\n", maxtime);
    }

    if (myid == 0) {
        plot(hist, gmax, gmin);
    }
    MPI_Finalize();
    free(X);
    return 0;
}
