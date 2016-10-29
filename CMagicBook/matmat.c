#include "mymagic.h"

void matmat(int n)
{
	double A [n*n];
	double B [n*n];
	double C [n*n];
	double s = gettime();
	for (int i=0; i < n; i++) {
		for (int j=0; j < n; j++) {
			for (int k=0; k < n; k++) {
				C[i * n + j] += A[i * n + k] * B[k * n + j];
			}
		}
	}
	double e = gettime();
	printf("%d x %d matrix: %f [ms]\n", n, n, (e-s));
}

int main()
{
	int n;
	scanf("%d", &n);
	matmat(n);
	return 0;
}  
