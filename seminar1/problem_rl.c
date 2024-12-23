#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long x,
                       unsigned long long y) {
	unsigned long long q;
	if (y > x){
		return gcd(y, x);
	}
	assert (y > 0);
	while (y < x){
		q = x % y;
		if (q == 0)
    		break;
		x = y;
		y = q;
	}
	return y;
}

int main() {
  long long x = 0, y = 0, g;
  int res;
  
  res = scanf("%lld %lld", &x, &y);
  assert(res == 2);
  x = (x<0) ? -x : x;
  y = (y<0) ? -y : y;
  g = gcd(x, y);
  printf("%llu\n", g);
  return 0;
}
