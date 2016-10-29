#include<stdio.h>

struct point {
	int x;
	int y;
} ;

int
main() {
	struct point a = {0, 0};
	const struct point b = {1, 1};
	const struct point *p = &a;
	struct point *p2 = &b;
	//b = a;
	//b.x = 2;
	//p = NULL;
	((struct point*)p)->x = 2;
	//struct point *const p3 = &a;
	//p3 = &a;
	return 0;
}
	
