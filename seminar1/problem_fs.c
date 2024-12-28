#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int dec2fact(unsigned int dec, unsigned int fact[]){
	int ind = 0;
    unsigned int base = 2;
	do {
		fact[ind++] =  dec % base;
		dec /= base;
        ++base;
	} while (dec > 0);
    return ind;
}

int main() {
  unsigned int x = 0;
  int res;

  res = scanf("%u", &x);
  assert(res == 1);
  
  unsigned int fact[32];
  int size = dec2fact(x, fact);
  for (int i = size-1; i>=0; --i){
      printf("%u.", fact[i]);
  }
  return 0;
}
