#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long gcd (long long x, long long y, long long * pa, long long * pb) {
  // r = x * a + y * b, r = GCD(x,y)
  long long q;
  long long tmp;
  long long r_prev;
  long long r;
  long long a_prev;
  long long a;
  long long b_prev;
  long long b;

  r_prev = (x<0) ? -x : x;
  r = (y<0) ? -y : y;
  a_prev = 1;
  a = 0;
  b_prev = 0;
  b = 1;
  while(r != 0) {
	  q = r_prev / r;
    tmp = r;
    r = r_prev - q * tmp;
    r_prev = tmp;

    tmp = a;
    a = a_prev - q * tmp;
    a_prev = tmp;

    tmp = b;
    b = b_prev - q * tmp;
    b_prev = tmp;
  }
  *pa = a_prev*((x<0) ? -1 : 1);
  *pb = b_prev*((y<0) ? -1 : 1);
  return r_prev;
}

int main() {
  long long x = 0, y = 0;
  int res;
  long long r = 0;
  long long a = 0;
  long long b = 0;

  res = scanf("%lld %lld", &x, &y);
  assert(res == 2);
  assert((x != 0) && (y != 0));

  r = gcd(x, y, &a, &b);

  printf("%lld %lld %lld", a, b, r);
  
  return 0;
}
