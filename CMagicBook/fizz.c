#include"mymagic.h"

	const char* format[4] = {
		"%d ", "Fizz ", "Buzz ", "FizzBuzz ",
	};

	int table[15] = {
		/*0=15*/ 3,
		/*1*/ 0, /*2*/ 0, /*3*/ 1, 
		/*4*/ 0, /*5*/ 2, /*6*/ 0, 
		/*7*/ 0, /*8*/ 0, /*9*/ 1, 
		/*10*/ 2, /*11*/ 0, /*12*/ 1, 
		/*13*/ 0, /*14*/ 0,  
	};

#define N 20

int main()
{
	for (int i = 1; i <= N; i++) {
		printf(format[table[i%15]], i);
	}
	for (int i = 1; i <= N; i++) {
		int fizz = !!(i % 3 == 0);
		int buzz = !!(i % 5 == 0);
		printf(format[(buzz << 1)+fizz], i);
	}
	for (int i = 1; i <= N; i++) {
		printf(&"%d \0\0\0Fizz \0Buzz \0FizzBuzz "[(((!!(i % 5 == 0)) << 1)+(!!(i % 3 == 0))) * 6], i);
	}
	return 0;	
}
