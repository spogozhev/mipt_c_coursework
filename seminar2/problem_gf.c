#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(long long x) ;
long long seqPrimesLength(long long a, long long b);
long long gf(long long n, long long a, long long b);

int main() {
  long long N = 0;
  long long ans = 0;
  long long a_best = 0;
  long long b_best = 0;
  long long tmp;
  int res;

  res = scanf("%lld", &N);
  assert(res == 1);
  assert(N > 0);
  
  for(long long a = -N+1; a < N; ++a ) {
    for(long long b = 1; b < N; ++b ) {
        tmp = seqPrimesLength(a, b);
        if (tmp>ans) {
            ans = tmp;
            a_best = a;
            b_best = b;
        }
    }
  }

  printf("%lld %lld %lld", a_best, b_best, ans);

  return 0;
}

long long gf(long long n, long long a, long long b){
    return n * n + a * n + b;
}

long long seqPrimesLength(long long a, long long b){
    long long n = 0;
    long long num;
    while(isPrime(gf(n, a, b))){        
        ++n;
    };
    return n;
}

bool isPrime(long long x) {
    if (x<2){
        return false;
    }
    if (x<4) {
        return true;
    }
    if (x%2==0){
        return false;
    }
    for(long long i=3; i*i<=x; i+=2){
        if ( (x % i) == 0 ){
            return false;
        }
    }
    return true;
}
