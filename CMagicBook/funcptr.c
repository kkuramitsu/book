#include"mymagic.h"

int mul(int a, int b) {
	return a*b;
}

void apply(char s[], int (*f)(int)) {
	int size = strlen(s);
	for(int i = 0; i < size; i++) {
		s[i] = f(s[i]);
	}
}

int undigit(int c) {
	if(c <= '0' && c <= '9') {
		return 'X';
	}
	return c;
}


int main() {
	int (*f)(int, int) = mul;
	(*f)(1,2);
	char buf[3] = {'c', '0', '\0'};
	apply(buf, toupper);
	apply(buf, undigit);
	return 0;
}

