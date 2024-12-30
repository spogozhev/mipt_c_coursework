#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned prime(unsigned x);

int main() {
  unsigned x = 0;
  unsigned ans = 1;
  int res;

  res = scanf("%u", &x);
  assert(res == 1);
  
  ans = prime(x);
  printf("%d", ans);
  return 0;
}

unsigned prime(unsigned x){
    unsigned res = 1;
    unsigned num = 1;
    bool flag;
    if (x == 1) {
        return 2;
    }
    while (x > 1){
        num += 2;
        flag = true;
        for(int i=2; i*i<=num; ++i){
            if ( (num % i) == 0 ){
                flag = false;
                break;
            }
        }
        if (flag){
            --x;
        }
    }
    return num;
}
