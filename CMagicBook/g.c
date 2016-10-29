#include<stdio.h>
#include<math.h>

#define u(n) (int)(pow(10, (int)log10(n)))

int h(int n)
{
	if(n < 10) {
		return n;
	}
	return h(n/10)*10;
}

int g(int n)
{
	if(n < 10) {
		return n;
	}
	return (n % 10)*u(n) + g(n/10);
	//return h(n) + g(n/10);
}

int g2 (int x) {
	int inv = 0;
	for(; x !=0; x /= 10) {
		inv = inv * 10 + x % 10;
	}
	return inv;
}

int g3(int x) {
	char buf[80];
	snprintf(buf, 80, "%d", x);
	int i, len = strlen(buf);
	for(i = 0; i < len/2; i++) {
		swap(buf+i, buf + (len - (i + 1)));
	}
	return (int)strtol(buf, NULL, 10);
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("g(%d)=%d\n", n, g(n));
	printf("g2(%d)=%d\n", n, g2(n));
	printf("g3(%d)=%d\n", n, g3(n));
	return 0;
}

