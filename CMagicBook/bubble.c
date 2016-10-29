#include "mymagic.h"

int a[10] = {
9, 1, 3, 7, 0, 5, 4, 2, 8, 6
};

void p() {
	for(int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void step(int m, int n) {
	for(int i = m; i <= (n-1); i++) {
		assert((i + 1) <= n);
		if(a[i] > a[i+1]) {
			int temp = a[i];
			a[i] = a[i+1];
			a[i+1] = temp;
		}
	}
}

int
main() 
{
	p();
	for(int i = 7; i > 2; i--) {
		step(2, i);
	}
	p();
	return 0;
}

