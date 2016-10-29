#include"mymagic.h"

int sum(int count, int a[]) {
  assert(count >= 0);
 
  int sum = 0; // ANSI-Cではエラー
  for (int i = 0; i < count; ++i) {  // ANSI-Cではエラー
    sum += a[i];
  }
  return sum;
}
 
int main(int argc, char **argv) {
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  P(data[1]);
  printf("sum = %d¥n", sum(sizeof(data) / sizeof(data[0]), data));
}

