#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

void usage() {
	printf("Usage: power num [num]\n");
	exit(1);
}

double strtod_or_die(const char *s) {
	double x = 0.0;
	char *r = NULL;
	x = strtod(s, &r);
	if(r == s) {
		usage();
	}
	return x;
}

int main(int ac, const char **av)
{
	double x = 0.0;
	double y = 2.0;
	if(ac == 1) {
		usage();
	}
	x = strtod_or_die(av[1]);
	if(ac > 2) {
		y = strtod_or_die(av[2]);
	}
	printf("%f\n", pow(x, y));
	return 0;
}
