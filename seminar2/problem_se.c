#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned numberOfPrimes(unsigned x);

int main() {
  unsigned x = 0;
  unsigned ans = 1;
  int res;

  res = scanf("%u", &x);
  assert(res == 1);
  
  ans = numberOfPrimes(x);
  printf("%d", ans);
  return 0;
}

unsigned numberOfPrimes(unsigned x) {
    unsigned res = 1;
    unsigned num = 3;
    unsigned cnt = 1;
    bool flag;
    if (x < 2) {
        return 0;
    }
    while (num <= x){
        flag = true;
        for(int i=2; i*i<=num; ++i){
            if ( (num % i) == 0 ){
                flag = false;
                break;
            }
        }
        if (flag){
            ++cnt;
        }
        num += 2;
    }
    return cnt;

}
