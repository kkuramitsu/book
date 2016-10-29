#include<stdio.h>

void matmul(double[] A, double[] B, double[] C, int N) {
	for (int i=0; i < N; i++) {
  		for (int j=0; j < N; j++) {
    			for (int k=0; k < N; k++) {
        			C[i*N+j] += A[i*N+k] * B[k*N+j];
    			}
  		}
	}
}

int main()
{
	return 0;
}

