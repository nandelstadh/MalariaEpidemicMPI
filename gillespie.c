#include "gillespie.h"

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
