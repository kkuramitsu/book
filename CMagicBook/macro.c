#include <stdio.h>

// 引数の数が違う、同じ関数に置き換える
#define DEBUG_PRINT(...)  printf(__VA_ARGS__)
#define DEBUG_PRINT2(fmt, ...)  printf(fmt, __VA_ARGS__)

// 引数の数が違う、別の関数に置き換える
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define SUM(...) GET_MACRO(__VA_ARGS__, sum3, sum2)(__VA_ARGS__)

int sum2(int a,int b) { return a+b; }
int sum3(int a,int b,int c) { return a+b+c; }

int main(void) {
    DEBUG_PRINT("num=%d\n",2);
    DEBUG_PRINT("num=%d,%d\n",3,4);

    DEBUG_PRINT2("num=%d\n",2);
    DEBUG_PRINT2("num=%d,%d\n",3,4);

    printf("SUM(2,3)=%d\n", SUM(2,3));
    printf("SUM(2,3,4)=%d\n", SUM(2,3,4));

    return 0;
}

