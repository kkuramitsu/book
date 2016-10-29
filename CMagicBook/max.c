#include "mymagic.h"
#include<stdarg.h>

int max2(int a, int b)
{
	return a > b ? a: b;
}

int max3(int a, int b, int c) 
{
	return max2(max2(a, b), c);
}

int _max(int a, ...)
{
	int maxvalue = a;
	va_list vargs;
	va_start(vargs, a);
	for(;;) {
		int value = va_arg(vargs, int);
		if(value == INT_MIN) {
			break;
		}
		if(value > maxvalue) {
			maxvalue = value;
		}
	}
	va_end(vargs);
	return maxvalue;
}

#define max(...) _max(__VA_ARGS__, INT_MIN)

int main()
{
	printf("%d\n", max(1,2));
	printf("%d\n", max(1,2,3));
	return 0;
}


