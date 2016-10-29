#include<stdio.h>
#include<assert.h>

static const char* digits = 
 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void printdigit(unsigned int x, int n) {
	printf("%lu\n", sizeof(digits));
	assert(n < 37);
	if(x >= n) {
		printdigit(x/n, n);
	}
	printf("%c", (int)digits[x%n]);
}

int main()
{
	int x, n;
	scanf("%d %d", &x, &n);
	printdigit(x, n);
	return 0;
}
	
