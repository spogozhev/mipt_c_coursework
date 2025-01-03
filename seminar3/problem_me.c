#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int majority_element(const int *parr, int len);

int main() {
  int res, n, i, answ;
  int *arr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  arr = (int*)calloc(n, sizeof(int));
  for (i = 0; i < n; ++i) {
    res = scanf("%d", arr + i);
    assert(res == 1);
  }

  answ = majority_element(arr, n);

  printf("%d\n", answ);

  free(arr);
  return 0;
}

int majority_element(const int *parr, int len) {
    int candidate = -1;
    int count = 0;
    int i;

    for (i = 0; i < len; ++i) {
        if (count == 0) {
            candidate = parr[i];
            count = 1;
        } else if (parr[i] == candidate) {
            ++count;
        } else {
            --count;
        }
    }

    // Validate
    count = 0;
    for (i = 0; i < len; ++i) {
        if (parr[i] == candidate) {
            ++count;
        }
    }

    return (count > len / 2) ? candidate : -1;
}