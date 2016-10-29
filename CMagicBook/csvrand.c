#include "mymagic.h"

static double rand1() {
	return (double)rand() / RAND_MAX;
}

static double gaussian(int k) {
	double sum = 0.0;
	for(int i = 0; i < k; i++) {
		sum += rand1();
	}
	return sum / k;
}

#define KMAX 10
#define RANGE 100
#define N 1000

void dump(FILE *fp)
{
	int dists[KMAX][RANGE+1] = {0};
	for(int k = 1; k < KMAX; k++) {
                for(int i = 0; i < N; i++) {
                        int r = round(gaussian(k) * 100);
                        dists[k][r]++;
                }
        }
	for(int i = 0; i <= RANGE; i++) {
		fprintf(fp, "%.2f", (double)i/100);
		for(int k = 1; k < KMAX; k++) {
			fprintf(fp, ",%d", dists[k][i]);
		}
		fprintf(fp, "\n");
	}
}

int main()
{
	dump(stdout);
	return 0;
}
