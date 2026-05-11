#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gillespie.h"
#include "prop.h"

int main(int argc, char** argv) {
    srand(time(0));
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
    int x[7] = {900, 900, 30, 330, 50, 270, 20};
    double w[15];

    double t = 0;
    while (t < T) {
        t += gillespie(x, w, P);
    }
    for (int i = 0; i < 7; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
    return 0;
}
