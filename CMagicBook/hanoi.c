#include"mymagic.h"

#define N 5
int X[N] = {0, 1, 1, 1, 1};
int Y[N] = {0, 0, 0, 0, 0};
int Z[N] = {0, 0, 0, 0, 0};

const char *items[] = {
	"     |     ",
	"     *     ",
	"    ***    ",
	"   *****   ",
	"  *******  ",
};

#define WX 3
#define WY 4

void layout(int w[][WY], int x, int tower[]) 
{
	int y = 3;
	for(int disk = N-1; disk > 0; disk--) {
		if(tower[disk] == 1) {
			w[x][y] = disk;
			y--;
		}
	}
}

void draw() 
{
	int w[WX][WY] = {0};
	layout(w, 0, X);
	layout(w, 1, Y);
	layout(w, 2, Z);
	for(int i = 0; i < WY; i++) {
		printf("%s %s %s\n", items[w[0][i]], items[w[1][i]], items[w[2][i]]);
	} 
	getchar(); // wait 
}

void move(int n, int from[], int to[], int other[]) 
{ 
	if (n > 0) {
		move(n-1, from, other, to);
		// move n from x to y
		from[n] = 0; to[n] = 1;
		draw();
		move(n-1, other, to, from);
	}
}


int
main()
{
	draw();
	move(4, X, Y, Z);
	return 0;
}
