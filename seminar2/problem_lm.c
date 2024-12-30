#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

unsigned long long lcm(unsigned long long a, unsigned long long b){
    unsigned long long g = gcd(a,b);
    return a / g * b;
}

unsigned long long lcmN(unsigned long long N){
    // LCM(2, 3, ..., N)
    unsigned long long ans = 6;
    if (N==2){
        return N;
    }
    for(unsigned long long an=4; an <= N; ++an){
        ans = lcm(ans, an);
    }
    return ans;
}

int main() {
    unsigned long long N = 0;
    unsigned long long ans = 0;
    int res;

    res = scanf("%lld", &N);
    assert(res == 1);
    ans = lcmN(N);
    printf("%lld", ans);

    return 0;
}

