#include<stdio.h>
#include<stdint.h>

char *binary(uint64_t n) {
        static char buf[65] = {0};
        for(int i = 63; i >= 0; i--) {
                buf[i] = (n % 2 == 0) ? '0' : '1';
                n /= 2;
        }
        return buf;
}

int main() {
	double d = 0.0;
	scanf("%lf", &d);
	uint64_t u = (uint64_t)d;
	printf("%f %s\n", d, binary(u));
	union num {
		double d;
		const uint64_t u;
	};
	union num n = {d};
	printf("%f %s\n", n.d, binary(n.u));
	
	uint64_t *p = (uint64_t*)&d;
	printf("%f %s\n", d, binary(*(p)));
	return 0;
}
