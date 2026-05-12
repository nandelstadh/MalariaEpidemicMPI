#include <mpi.h>

#include "prop.h"
#define NUM_BUCKETS 20
#define PLOT 1

double gillespie(int* x, double* w, const int P[15][7]);
void histogram(int n, int X[n][7], int hist[NUM_BUCKETS], int* gmax, int* gmin);
void plot(int hist[NUM_BUCKETS], int gmax, int gmin);
