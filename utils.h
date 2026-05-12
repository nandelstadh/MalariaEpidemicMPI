#include <mpi.h>

#include "prop.h"

double gillespie(int* x, double* w, const int P[15][7]);
void histogram(int n, int X[n][7]);
