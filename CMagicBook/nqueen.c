#include "mymagic.h"

#define B(x,y)  ((x * n) + y)

#define EMPTY    0
#define QUEEN    1
#define DISABLED 2
#define ENABLED -2
#define N 25

void p(int board[][N], int n, int solution)
{
	/*
	printf("Solution %d:\n", solution);
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			printf(board[x][y] == QUEEN ? "Q" : ".");
		}
		printf("\n");
	}
	*/
}

void mark(int board[][N], int n, int x0, int y0, int dx, int dy, int d)
{
	int x = x0 + dx;
	int y = y0 + dy;
	if(0 <= x && x < n && 0 <= y && y < n) {
		board[x][y] += d;
		mark(board, n, x, y, dx, dy, d);
	}
}

void change(int board[][N], int n, int x, int y, int d) {
	mark(board, n, x, y, 0, +1, d);
	mark(board, n, x, y, +1, 0, d);
	mark(board, n, x, y, +1, +1, d);
	mark(board, n, x, y, -1, +1, d);
}

int solve(int board[][N], int n, int y, int solution) {
	if (y == n) {
		solution++;
		p(board, n, solution);
		return solution;
	}
	for(int x = 0; x < n; x++) {
		if (board[x][y] == EMPTY) {
			board[x][y] = QUEEN;
			change(board, n, x, y, DISABLED);
			solution = solve(board, n, y+1, solution);
			change(board, n, x, y, ENABLED);
			board[x][y] = EMPTY;
		}
	}
	return solution;
}

int main()
{
	int board[N][N] = {0};
	int n = 8;
	scanf("%d", &n);
	assert(n <= N);
	uint64_t s = gettime();	
	int sol = solve(board, n, 0, 0);
	uint64_t e = gettime();
	printf("Solution: %d %fms\n", sol, (e-s)/10.0); 
	return 0;
}

