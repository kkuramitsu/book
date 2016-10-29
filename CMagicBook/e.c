#include<stdio.h>
#include<stdint.h>
#include<math.h>

#define E 2.71828182845904523536028747135266249775724709369995957496696762772L
#define T long double
#define U 1.0L

uint64_t fact64(uint64_t n) {
	return n == 1 ? 1LL : fact64(n-1) * n;
}

T ifact(int n)
{
	return n == 1 ? 1.0L : ifact(n-1) * (1.0L / n);
}

T ee(int n) {
	T result = ifact(n);
	for(int i = n-1; i > 0; i--) {
		result += ifact(i);
	}
	return result + U;
}

int main()
{
	int i;
	float e0 = 1.0;
	T e = U;
	T e2 = U;
	for(i = 1; i < 100; i++) {
		e +=  ifact(i);
		e2 += (U / fact64(i));
		printf("%d\t2.71828182845904523536028747135266249775724", i);
		printf("\n\t%.70Lf\n\t%.70Lf\n", ee(i), e2);
	}
	return 0;
}

