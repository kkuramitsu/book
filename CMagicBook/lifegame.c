/*
 * lifegame.c
 */

#include <stdio.h>
#include <stdlib.h>
#define M 29 
#define N 15
#define MAX_GEN 1000

int life[N + 2][M + 2] = {0};


void init()
{
    life[N/2+1][M/2-1] = 1;
    life[N/2+1][M/2+0] = 1;
    life[N/2+1][M/2+1] = 1;
    life[N/2+1][M/2+2] = 1;
    life[N/2+1][M/2+3] = 1;
}

void dump()
{
    for (int i=1; i <= N; i++) {
        for (int j=1; j <=M; j++) {
            printf( (life[i][j] == 1) ? "*" : ".");
        }
        printf("\n");
    }
}

static int countup(int i, int j) {
    return life[i-1][j-1] + life[i-1][j] + life[i-1][j+1]
        + life[i][j-1]  /*+ life[i][j]*/ + life[i][j+1]
        + life[i+1][j-1] + life[i+1][j] + life[i+1][j+1];
}

static void step()
{
    int c[N + 2][M + 2] = {0};
    for (int i=1; i <= N; i++) {
        for (int j=1; j <=M; j++) {
            c[i][j] = countup(i,j);
        }
    }
    for (int i=1; i <= N; i++) {
        for (int j=1; j <=M; j++) {
            if(c[i][j] >= 3 && life[i][j] == 0) {
                life[i][j] = 1;
            }
            else if((c[i][j] == 2 || c[i][j] == 3) && life[i][j] == 1) {
                life[i][j] = 1;
            }
            else {
                life[i][j] = 0;
            }
        }
    }
}


int main()
{
    init();
    for(int t = 0; t <= MAX_GEN; t++) {
        dump();
        step();
	printf("Hit [enter] key");
        getchar();
    }
    return 0;
}
