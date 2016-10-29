#include"mymagic.h"

double f(double x, double n) {
	return x * x * x - n;
}

double qbrt(double n, double x0, double x1) 
{ 
	double m = (x0 + x1) / 2;
	if(fabs(f(m, n)) <= DBL_EPSILON) {
		return m; 
	}
	if(f(x0,n) * f(m,n) < 0.0) { 
		return qbrt(n, x0, m);
	}
	return qbrt(n, m, x1); 
}

int main()
{
	printf("%f", qbrt(3, 0, 3));
	return 0;
}

