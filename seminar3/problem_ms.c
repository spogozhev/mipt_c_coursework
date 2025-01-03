#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *arr, int l, int m, int r);

void merge_sort_imp(int *arr, int l, int r) {
  int m;
  if (l >= r)
    return;
  m = (l + r) / 2;
  merge_sort_imp(arr, l, m);
  merge_sort_imp(arr, m + 1, r);
  merge(arr, l, m, r);
}

int main() {
  int res, n, i;
  int *parr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  parr = (int*)calloc(n, sizeof(int));

  for (i = 0; i < n; ++i) {
    res = scanf("%d", parr + i);
    assert(res == 1);
  }

  merge_sort_imp(parr, 0, n - 1);

  for (i = 0; i < n; ++i)
    printf("%d ", parr[i]);
  printf("\n");

  free(parr);
}

void merge(int *arr, int l, int m, int r){
    int* parr;
    int index;
    int leftBegin = l;
    int rightBegin = m + 1;
    int tmp;
    if (l>=r) {
        return;
    }
    if (r-l==1){
        if ( arr[r] < arr[l] ) {
            tmp = arr[r];
            arr[r] = arr[l];
            arr[l] = tmp;
        }
        return;
    }

    parr = (int*)calloc(r+1-l, sizeof(int));
    index = 0;
    leftBegin = l;
    rightBegin = m + 1;
    while(leftBegin <= m && rightBegin<=r){
        if (arr[leftBegin] < arr[rightBegin]){
            parr[index] = arr[leftBegin];
            ++leftBegin;
            ++index;
        } else {
            parr[index] = arr[rightBegin];
            ++rightBegin;
            ++index;
        }
    }

    while(leftBegin <= m){
        parr[index] = arr[leftBegin];
        ++leftBegin;
        ++index;
    }
    
    while(rightBegin<=r){
        parr[index] = arr[rightBegin];
        ++rightBegin;
        ++index;
    }

    index = 0;
    leftBegin = l;
    while (leftBegin<=r){
        arr[leftBegin] = parr[index];
        ++leftBegin;
        ++index;
    }

    free(parr);
}
