#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int sum = 0;
  int res;
  char ch;
  int count = 0;
  for(;;){
    res = scanf("%c", &ch);
    if (res!=1){
      break;
    }
    sum += ch;
    ++count;
  }

  printf("%d\n", sum);
  printf("symbols: %d\n", count);

  return 0;
}
