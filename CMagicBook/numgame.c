#include<stdio.h>
#include<stdlib.h> // rand()
#include<time.h>   // time()

#define R  100
#define N  5

int main()
{
	int i = 0, r = 0;
	srand(time(NULL));
	r = rand() % R;
	for(i = 0; i < N; i++) {
		int x = 0;
		printf("Guess my number? ");
		scanf("%d", &x);
		if(r == x) {
			printf("Bingo!!\n");
			break;
		}
		if(r < x) {
			printf("Too big.\n");
			//continue;
		}
		if(r > x) {
			printf("Too small.\n");
			//continue;
		}
	}/*for*/
	printf("You lose");
	return 0;
}

