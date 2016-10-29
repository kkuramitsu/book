#include"mymagic.h"

void p(int a[], int len) {
	printf("(");
	for(int i = 0; i < len; i++) {
		if(i > 0) {
			printf(" ");
		}
		printf("%d", a[i]);
	}
	printf(") ");
}

void swap(int a[], int l, int r) {
	int tmp = a[l];
	a[l] = a[r];
	a[r] = tmp;
}

void perm(int a[], int len, int loc)
{
	if(loc + 1 == len) {
		p(a, len);
		return;
	}
	perm(a, len, loc+1);
	for(int i = loc + 1; i < len; i++) {
		swap(a, loc, i);
		perm(a, len, loc+1);
		swap(a, loc, i);
	}
}

int main() 
{
	int a[4] = {1, 2, 3, 4};
	perm(a, 4, 0);
	return 0;
}


