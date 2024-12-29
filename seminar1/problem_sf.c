#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void fib_system(unsigned x) {
    unsigned fibNumbers[2] = {1, 2};
    unsigned tmp;
    while( fibNumbers[1] < x ){
        tmp = (fibNumbers[0] + fibNumbers[1]);
        fibNumbers[0] = fibNumbers[1];
        fibNumbers[1] = tmp;
    }

    while(fibNumbers[1] >= 2){
        if (x>=fibNumbers[0]){
            x-=fibNumbers[0];
            printf("1");
        }else {
            printf("0");
        }
        tmp = fibNumbers[1] - fibNumbers[0];
        fibNumbers[1] = fibNumbers[0];
        fibNumbers[0] = tmp;
    }
}

int main() {
  unsigned long long  x = 0;
  int res;

  res = scanf("%lld", &x);
  assert(res == 1);
  
  fib_system(x);
  return 0;
}
