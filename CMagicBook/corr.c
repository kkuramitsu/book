#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double corr(double x[], double y[]) {
	double xmean = 0.0, ymean = 0.0;
	for(int i = 0; i < 100; i++) {
		xmean += x[i];
		ymean += y[i];
	}
	xmean /= 100;
	ymean /= 100;
	double rxy = 0.0, rx2 = 0.0, ry2 = 0.0;
	for(int i = 0; i < 100; i++) {
		rxy = (x[i] - xmean) * (y[i] - ymean);
		rx2 = (x[i] - xmean) * (x[i] - xmean);
		ry2 = (y[i] - ymean) * (y[i] - ymean);
	}
	return rxy / sqrt(rx2 * ry2);
}
int main() {
	double x[10];
	double y[10];
	corr(x,y);
	return 0;
}
