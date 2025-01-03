#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int lsd(int *parr, int n, int digit);

int main() {
  int res, n, i, digit;
  int *arr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  arr = (int*)calloc(n, sizeof(int));
  for (i = 0; i < n; ++i) {
    res = scanf("%d", arr + i);
    assert(res == 1);
  }

  res = scanf("%d", &digit);
  assert(res == 1);

  res = lsd(arr, n, digit);
  if (res==0){
    free(arr);  
    abort();
  }
  for (i = 0; i < n; ++i) {
    printf("%d ", arr[i]);
  }

  free(arr);
  return 0;
}

int lsd(int *parr, int n, int radix) {
    int * M;
    int bucket[10] = {0};
    int i, tmp;
    int count;
    int digit;
    int d = 10;

    while(radix>0){
        d *= 10;
        --radix;
    }

    M = (int*)calloc(n, sizeof(int));
    if (M == NULL){
        return 0;
    }

    for(i=0; i < n; ++i){
        digit = (parr[i]%d) / (d/10) ;
        ++bucket[digit];
    }
    
    count = 0;
    for(i=0; i<10; ++i){
        tmp = bucket[i];
        bucket[i] = count;
        count += tmp;
    }

    for(i=0; i < n; ++i){
        digit = (parr[i]%d) / (d/10) ;
        M[bucket[digit]] = parr[i];
        ++bucket[digit];
    }

    for(i=0; i < n; ++i){
        parr[i] = M[i];
    }

    free(M);
    return 1;
}