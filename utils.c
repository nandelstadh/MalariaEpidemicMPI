#include "utils.h"

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prop.h"

double gillespie(int* x, double* w, const int P[15][7]) {
    prop(x, w);
    double sums[15];
    sums[0] = w[0];
    for (int r = 1; r < 15; r++) {
        sums[r] = sums[r - 1] + w[r];
    }
    const double a0 = sums[14];
    const double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
    const double u2 = (double)rand() / (double)RAND_MAX;
    const double tau = -log(u1) / a0;
    if (tau < 0) printf("Tau is less than 0, not good\n");
    const double prod = a0 * u2;

    int r = 0;
    while (sums[r] < prod) {
        r++;
    }

    for (int i = 0; i < 7; i++) {
        x[i] += P[r][i];
    }
    return tau;
};

void histogram(int n, int X[n][7], int hist[NUM_BUCKETS], int* gmax, int* gmin) {
    int max, min;
    max = X[0][0];
    min = X[0][0];
    for (int i = 0; i < n; i++) {
        if (X[i][0] < min) min = X[i][0];
        if (X[i][0] > max) max = X[i][0];
    }

    int n_procs, myid;
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Reduce(&max, gmax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&min, gmin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Bcast(gmax, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(gmin, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double bucket_width = ((double)(*gmax - *gmin)) / NUM_BUCKETS;
    if (bucket_width == 0) {
        printf("gmin == gmax, something went wrong\n");
        return;
    }

    int buckets[NUM_BUCKETS] = {0};

    // Fill histogram
    for (size_t i = 0; i < n; i++) {
        int index = (int)((X[i][0] - *gmin) / bucket_width);

        // Ensure max value goes into last bucket
        if (index == NUM_BUCKETS)
            index = NUM_BUCKETS - 1;

        buckets[index]++;
    }

    MPI_Reduce(&buckets, hist, NUM_BUCKETS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myid == 0) {
        /* printf("Min: %d, Max: %d\n", *gmin, *gmax); */
        /* for (int i = 0; i < NUM_BUCKETS; i++) { */
        /*     printf("%d ", hist[i]); */
        /* } */
        /* printf("\n"); */
    }
}

void plot(int hist[NUM_BUCKETS], int gmax, int gmin) {
    int n_procs, myid;
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    FILE* f = fopen("data/histogram.csv", "w");
    fprintf(f, "left,right,count\n");
    double bw = (double)(gmax - gmin) / NUM_BUCKETS;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        double left = gmin + i * bw;
        double right = left + bw;
        fprintf(f, "%.10f,%.10f,%d\n", left, right, hist[i]);
    }
    fclose(f);

    if (PLOT) {
        int rc = system("python plot_hist.py");
        if (rc != 0) fprintf(stderr, "plot script failed\n");
    }
}
