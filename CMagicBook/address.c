#include<stdio.h>

int x = 0, y = 0, z = 0;

int main() 
{
	int a = 0;
	int b = 0;
	int c = 0;
	int nums[10] = {0};
	printf("x,y,z = %p %p %p\n", &x, &y, &z); 
	printf("a,b,c = %p %p %p\n", &a, &b, &c);
	for(int i = 0; i < 10; i++) {
		printf("nums[%d] = %p\n", i, &nums[i]);
	}
        printf("nums[100] = %p\n", &nums[100]);
	printf("systems: %ld\n", sizeof(&a)*8);
	return 0;
}


