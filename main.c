#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prop.h"
#include "utils.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Expected: main n\n");
        return -1;
    }
    int n = atoi(argv[1]);

    // Initializing MPI stuff
    MPI_Init(&argc, &argv);
    int n_procs, myid;
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Initializing seed anv variables
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
    double times[4] = {0};
    const double checkpoints[4] = {25, 50, 75, 100};
    int k = 0;

    // Start of the timed section
    double start = MPI_Wtime();

    // Main loop running n simulations on the process
    for (int i = 0; i < n; i++) {
        X[i][0] = 900;
        X[i][1] = 900;
        X[i][2] = 30;
        X[i][3] = 330;
        X[i][4] = 50;
        X[i][5] = 270;
        X[i][6] = 20;

        t = 0;
        k = 0;
        double passed_time[4] = {0};
        // Main loop for each individual process
        double simulation_start = MPI_Wtime();
        while (t < T) {
            double t_prev = t;
            t += gillespie(X[i], w, P);
            while (k < 4 && t_prev < checkpoints[k] && t >= checkpoints[k]) {
                passed_time[k] = MPI_Wtime() - simulation_start;
                k++;
            }
        }
        times[0] += passed_time[0];
        times[1] += passed_time[1] - passed_time[0];
        times[2] += passed_time[2] - passed_time[1];
        times[3] += passed_time[3] - passed_time[2];
    }

    histogram(n, X, hist, &gmax, &gmin);
    // End of the timed section
    double time = MPI_Wtime() - start;

    // Reducing interval times
    double all_times[n_procs][4];
    double global_times[4] = {0};

    MPI_Win win_times;

    MPI_Win_create(all_times, myid == 0 ? n_procs * 4 * sizeof(double) : 0, sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &win_times);

    MPI_Win_fence(0, win_times);
    MPI_Put(times, 4, MPI_DOUBLE, 0, myid * 4, 4, MPI_DOUBLE, win_times);
    MPI_Win_fence(0, win_times);

    // Reducing global times
    double maxtime;
    MPI_Reduce(&time, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Local computations of times on root, and printing+plotting
    if (myid == 0) {
        for (int p = 0; p < n_procs; p++) {
            for (int i = 0; i < 4; i++) {
                global_times[i] += all_times[p][i];
            }
        }

        for (int i = 0; i < 4; i++) {
            global_times[i] = global_times[i] / (n_procs * n);
            printf("%f ", global_times[i]);
        }
        printf("\n");

        printf("Time: %f\n", maxtime);

        plot(hist, gmax, gmin);
    }

    // Freeing memory
    MPI_Win_free(&win_times);
    free(X);
    MPI_Finalize();
    return 0;
}
