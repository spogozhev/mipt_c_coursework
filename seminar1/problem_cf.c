#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  long long x = 0, y = 0;
  int res;
  long long q, r;

  res = scanf("%lld %lld", &x, &y);
  assert(res == 2);
  x = (x<0) ? -x : x;
  y = (y<0) ? -y : y;

  assert(y > 0);

  while(y>0){
	q = x / y;
	r = x - q * y; // r = x % y
  	printf("%lld ", q);
	x = y;
	y = r;
  }

  return 0;
}
