#include<stdio.h>

char *binary(unsigned int n) {
	static char buf[33] = {0};
	for(int i = 31; i >= 0; i--) {
		buf[i] = (n % 2 == 0) ? '0' : '1';
		n /= 2;
	}
  	return buf;
}

int
main() {
	printf("%s", binary(4));
	return 0;
}
