#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void ChooseSortStep(int *arr, int size, int last){
    int index = last;
    int tmp;
    for(int i = last+1; i < size; ++i){
        if (arr[i] < arr[index]){
            index = i;
        }
    }
    if (index > last){
        tmp = arr[index];
        arr[index] = arr[last];
        arr[last] = tmp;
    }
}

int main() {
  int n;
  int i;
  int last;
  int res;
  int *parr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  parr = (int*)calloc(n, sizeof(int));

  if(parr==NULL) {
    abort();
  }
  
  for (i = 0; i < n; ++i) {
    res = scanf("%d", parr + i);
    assert(res == 1);
  }

  res = scanf("%d", &last);
  assert(res == 1);
  assert(last < n);
  
  ChooseSortStep(parr, n, last);

  for (i = 0; i < n; ++i)
    printf("%d ", parr[i]);

  free(parr);
  return 0;
}
