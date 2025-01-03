#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int moveright(int *arr, int key, int last){
    int index = last-1;
    while(index>=0 && key<arr[index]){
        arr[index+1] = arr[index];
        --index;
    }
    return index+1;
}

void inssort(int *arr, int len) {
  for (int i = 0; i < len; ++i) {
    int key = arr[i];
    int pos = moveright(arr, key, i);
    arr[pos] = key;
  }
}

int main() {
  int res, answ, n, last, i;
  int *parr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  parr = (int*)calloc(n, sizeof(int));

  for (i = 0; i < n; ++i) {
    res = scanf("%d", parr + i);
    assert(res == 1);
  }

  res = scanf("%d", &last);
  assert(res == 1);
  assert(last < n);
  
  answ = moveright(parr, parr[last], last);

  for (i = 0; i < n; ++i)
    printf("%d ", parr[i]);
  printf("\n");
  printf("%d\n", answ);
  free(parr);
}
