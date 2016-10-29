#include "mymagic.h"

int a[7] = {1, 1, 2, 3, 5,  8, 13};

int
main()
{
	int n = 0;
	scanf("%d", &n);
	for(int i = 0, c = 0; i < n; i++, c++) {
		if(c == 7) {
			c = 0;
		}
		assert(c < 7);
		printf("%d ", a[c]);
	}
	/*
	for(int j = 0; j < (n / 7) + 1 ; j++) {
		for(int i = 0; i < 7; i++) {
			if(n == 7 * j + i) {
				break;
			}
			assert(i < 7);
			printf("%d ", a[i]);
		}
	}
	*/
	return 0;
}
