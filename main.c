#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gillespie.h"
#include "prop.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Expected: main n\n");
        return -1;
    }
    int n = atoi(argv[1]);
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
    int X[n][7];
    double w[15];
    double t = 0;

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
        for (int j = 0; j < 7; j++) {
            printf("%d ", X[i][j]);
        }
        printf("\n");
    }
    return 0;
}
