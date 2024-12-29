#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long fib(unsigned long long x, unsigned long long m){
    unsigned long long fibNumbers[2] = {0, 1};
    unsigned long long tmp;
    if (x < 2) return fibNumbers[x];
    for(unsigned long long i = 2; i<=x; ++i){
        tmp = (fibNumbers[0] + fibNumbers[1]) % m;
        fibNumbers[0] = fibNumbers[1];
        fibNumbers[1] = tmp;
    }
    return fibNumbers[1];
}

unsigned piz(unsigned long long m){
    unsigned long long current = 0;
    unsigned long long next = 1;
    unsigned period = 0;
    unsigned long long old_next = 0;
    do {
        old_next = next;
        next = (current + next) % m;
        current = old_next;
        ++period;
    } while(!(current==0 && next==1));
    return period;
}

int main() {
  unsigned long long  x = 0;
  unsigned long long  m = 0;
  unsigned long long  f = 0;
  unsigned p = 0;  
  int res;

  res = scanf("%lld%lld", &x, &m);
  assert(res == 2);
  assert(m != 0);
  
  p = piz(m);
  f = fib(x%p, m);
  printf("%lld %u", f, p);
  return 0;
}
