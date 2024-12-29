#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned fib(unsigned x, unsigned m){
    unsigned fibNumbers[2] = {0, 1};
    unsigned tmp;
    if (x < 2) return fibNumbers[x];
    for(int i = 2; i<=x; ++i){
        tmp = (fibNumbers[0] + fibNumbers[1]) % m;
        fibNumbers[0] = fibNumbers[1];
        fibNumbers[1] = tmp;
    }
    return fibNumbers[1];
}

int main() {
  unsigned int x = 0;
  unsigned int m = 0;
  unsigned int result = 0;
  int res;

  res = scanf("%u%u", &x, &m);
  assert(res == 2);
  assert(m != 0);
  
  result = fib(x, m);
  printf("%u", result);
  return 0;
}
