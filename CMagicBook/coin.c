#include "mymagic.h"

#define N 5

int value[N] = {
	50,40,7,1
};

void solve(int price) 
{
	int p = price;
	int count[N] = {0};
	printf("greedy %d ", price);
	for(int coin = 0; coin < N; coin++) {
		count[coin] = p/value[coin];
		p = p % value[coin];
		printf("(%d,%d) ", value[coin], count[coin]);
	}
	printf("sum : %d\n", count[0]+count[1]+count[2]+count[3]);
}


struct combi {
	int sum;
	int count[N];
};

#define MAX 1000
struct combi memo[MAX] = {0};

void dp2(int x) {
	for(int p = 0; p < x; p++) {
		for(int coin = 0; coin < N; coin++) {
			int pp = p + value[coin];
			if(pp < MAX && (memo[pp].sum == 0 || memo[p].sum < memo[pp].sum)) {
				memo[pp] = memo[p];
				memo[pp].sum++;
				memo[pp].count[coin]++;
			}
		}
	}
	for(int coin = 0; coin < N; coin++) {
                printf("(%d,%d) ", value[coin], memo[x].count[coin]);
        }
	printf("sum : %d\n", memo[x].sum);

}

int main()
{
	dp2(127);
	return 0;
}
	
