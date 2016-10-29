#include"mymagic.h"

int fact(int n) {
	assert(n > 0);
	if(n == 1) {
		return 1;
	}
	return n * fact (n-1);
}

int main()
{
	return fact(-1);
}

