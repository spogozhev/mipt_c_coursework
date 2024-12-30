#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned long long mult_mod(unsigned long long n, unsigned long long k, unsigned long long m){
    unsigned long long mult = n % m;
    unsigned long long prod = 0;
    while ( k > 0 ){
        if ((k%2) == 1){
            prod = (prod + mult) % m;
            k -= 1; // --k;
        }
        mult = (mult + mult) % m;
        k /= 2; // k >>= 1;
    }
    return prod;
}

unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m){
    unsigned long long mult = n % m;
    unsigned long long prod = 1;
    while ( k > 0 ){
        if ((k%2) == 1){
            prod = mult_mod(prod, mult, m); 
            //prod = (prod * mult) % m;
            k -= 1; // --k;
        }
        mult = mult_mod(mult, mult, m); 
        //mult = (mult * mult) % m;
        k /= 2; // k >>= 1;
    }
    return prod;
}

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

bool testFerma(unsigned long long x){
    unsigned long long a;
    int attempts = 10;
    if (x<2) return false;
    if (x<4) return true;
    if (x%2==0) return false;
    do{
        do {
            a = rand() + 1;
            a = a / gcd(a, x);
        } while(a==1);
        if (pow_mod(a, x-1, x) != 1){
            return false;
        }
        --attempts;
    }while(attempts>0);
    return true;
}

unsigned long long primeLikeFibonacci(unsigned long long k, unsigned long long n){
    unsigned long long fibNumbers[2] = {0, 1};
    unsigned long long maximum = (1ULL<<60);
    unsigned long long tmp;
    while( fibNumbers[1] < maximum ){
        tmp = (n * fibNumbers[0] + k * fibNumbers[1]);
        fibNumbers[0] = fibNumbers[1];
        fibNumbers[1] = tmp;
    }

    while(fibNumbers[1] > 1){
        if (testFerma(fibNumbers[0])){
            return fibNumbers[0];
        }
        tmp = (fibNumbers[1] - k * fibNumbers[0]) / n;
        fibNumbers[1] = fibNumbers[0];
        fibNumbers[0] = tmp;
    }
    return 0;
}

int main()
{
    unsigned long long k;
    unsigned long long n;
    unsigned long long ans;
    int res;
    
    res = scanf("%llu%llu", &k, &n);
    assert(res == 2);

    ans = primeLikeFibonacci(k, n);
    printf("%llu", ans);

    return 0;
}

