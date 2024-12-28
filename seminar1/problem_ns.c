#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void dec2base(unsigned int dec, unsigned int base, char str[]){
	int ind = 0;
    char tmp;
	do {
		unsigned int digit = dec % base;
		str[ind++] = (digit<10) ? ('0'+digit) : ('A' + (digit-10));
		dec /= base;
	} while (dec > 0);
	str[ind] = '\0';
	for(int i=0, j=ind-1; i<j; ++i, --j){
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
	}
}

int main() {
  unsigned int x = 0;
  unsigned int y = 0;
  int res;

  res = scanf("%u %u", &x, &y);
  assert(res == 2);
  assert((y > 1) && (y < 11));

  char str[sizeof(unsigned int) * 8 + 1];
  dec2base(x, y, str);
  printf("%s", str);
  return 0;
}
