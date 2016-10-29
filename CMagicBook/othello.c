#include"mymagic.h"

int board[100] = {0};
#define BORDER 0;
#define BLACK  1
#define WHITE  2
#define BORDER 3

void init(int board[]) {

}

void display(int board[]) {
	for(int i = 0; i < 100; i++) {
		if(i % 10 == 0 && i > 0) {
			printf("\n");
		}
		printf(board[i]);
	}
	printf("\n");
}

bool check(int b[]) {
	
			

