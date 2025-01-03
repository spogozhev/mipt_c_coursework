#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int cst(const int *parr, int len, int * bucket, int bucket_size);

int main() {
  int res, n, i, answ;
  int *arr;
  const int bucket_size = 11;
  int bucket[bucket_size];

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  arr = (int*)calloc(n, sizeof(int));
  for (i = 0; i < n; ++i) {
    res = scanf("%d", arr + i);
    assert(res == 1);
  }

  answ = cst(arr, n, bucket, bucket_size);

  answ = bucket_size;
  while (answ>0 && bucket[answ-1]==0){
    --answ;
  }
  for (i = 0; i < answ; ++i) {
    printf("%d ", bucket[i]);
  }

  free(arr);
  return 0;
}

int cst(const int *parr, int len, int * bucket, int bucket_size) {
    int i;
    for(i=0; i < bucket_size; ++i){
        bucket[i] = 0;
    }
    for(i=0; i<len; ++i){
        assert(parr[i] < bucket_size);
        assert(parr[i] >= 0);
        ++bucket[parr[i]];
    }
    return 1;
}