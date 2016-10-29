#include<stdio.h>
int main2() {
	double x = 0.0;
	printf("x="); 
	scanf("%lf", &x);
	printf("x=%.2f %.2e %.3f %3.2f%%\n", x, x, x, (100*x));
	return 0;
}
int main()
{
	long x = 0;
	scanf("%ld", &x);
	printf("x=%ld %lx\n", x, x);
	return 0;
}

