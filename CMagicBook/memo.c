#include<stdio.h>
#include<stdint.h>
#include<assert.h>

#define MAX 200

int fibo (int n) {
	assert(0< n && n < MAX);
	static int memo[MAX+1] = {0LL, 1LL, 1LL, 0LL}; 
	if(memo[n] == 0LL) {
		memo[n] = fibo(n-1) + fibo(n-2);
	}
	return memo[n];
}

#define DIG 10000000000000000LL

static uint64_t memo2[MAX+1] = {0LL, 0LL}; 
static uint64_t memo[MAX+1] = {0LL, 1LL, 1LL, 0LL}; 
void fibox2 (int n) {
	assert(0< n && n < MAX);
	if(memo[n] == 0LL) {
		fibox2(n-1);
		fibox2(n-2);
		memo2[n] = (memo2[n-1] + memo2[n-2] + (memo[n-1] + memo[n-2]) / DIG) %DIG;
		memo[n] = (memo[n-1] + memo[n-2]) % DIG;
	}
}

int main()
{
	for(int i = 1; i <= 100; i++) {
		printf("%d, %d\n", i, fibo(i));
		fibox2(i);
		printf("%d, %16llu%016llu\n", i, memo2[i], memo[i]);
	}
	return 0;
}

