#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned mult_mod(unsigned n, unsigned k, unsigned m){
    unsigned mult = n % m;
    unsigned prod = 0;
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

unsigned pow_mod(unsigned n, unsigned k, unsigned m){
    unsigned mult = n % m;
    unsigned prod = 1;
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

// Euler's Totient function
unsigned eulerTotient(unsigned m) {
    unsigned result = m;
    for (unsigned p = 2; p * p <= m; ++p) {
        if (m % p == 0) {
            do {
                m /= p;
            } while (m % p == 0);
            result -= result / p; // result = (result*(a-1))/a;
        }
    }
    if (m > 1) {
        result -= result / m; // result = (result*(m-1))/m;
    }
    return result;
}

unsigned phiLimit(unsigned n) {
    unsigned res = 0;
    while (n != 1) {
        n = eulerTotient(n);
        ++res;
    }
    return res;
}

unsigned phi(unsigned n, unsigned d) {
    unsigned res = n;
    for (unsigned i = 0; i < d && res != 1; i++) 
        res = eulerTotient(res);
    return res;
}

unsigned spow_mod(unsigned n, unsigned k, unsigned m){
    if (m == 1) return 0;
    if (k == 0) return 1;
    if (n == 1) return 1;
    if (k == 1) return n % m;
    if (n % m == 0) return 0;
    
    unsigned power = n % m;
    unsigned limit = phiLimit(m);
    limit = (k < limit) ? k : limit;
    limit = (2 < limit) ? limit : 2;
    for (int i = limit - 1; i > 0; i--) {
        unsigned to = phi(m, i - 1);
        power =  pow_mod(n, power, to);
        if (power == 0 && i != 1) 
            power = to;
    }
    return power;
}

int main() {
  unsigned int a = 0;
  unsigned int b = 0;
  unsigned int n = 0;
  unsigned int result = 0;
  int res;

  res = scanf("%u %u %u", &a, &b, &n);
  assert(res == 3);
  assert(n != 0);
  
  result = spow_mod(a, b, n);
  printf("%u", result);
  return 0;
}
