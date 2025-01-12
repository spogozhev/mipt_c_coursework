// + https://education.yandex.ru/handbook/algorithms/article/zadacha-o-ryukzake
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int read_weights(int **weights){
    int res;
    int count;
    res = scanf("%d", &count);
    if (res != 1){
        weights = NULL;
        return 0;
    }
    *weights = (int *)calloc(count, sizeof(int));
    if (weights == NULL){
        return 0;
    }
  
    for(int i = 0; i < count; ++i) {
        res = scanf("%d", (*weights) + i);
        if (res != 1){
            return -1;
        }
    }
    return count;
}


#ifndef max
int max(int x, int y) {
    return (x < y) ? y : x;
}
#endif

int knapsack(int capacity, int* weights, int count) {
    int** table = (int**)calloc(count + 1, sizeof(int*));
    assert(table != NULL);
    int ans = 0;
    for (int i = 0; i <= count; ++i) {
        table[i] = (int*)calloc(capacity + 1, sizeof(int));
        assert(table[i] != NULL);
    }
    for (int i = 1; i <= count; ++i) {
        for (int k = 1; k <= capacity; ++k) {
            if (k >= weights[i-1]) {
                table[i][k] = max(table[i - 1][k], table[i - 1][k - weights[i-1]]+1);
            }
            else {
                table[i][k] = table[i - 1][k];
            }
        }
    }
    int k = capacity;
    for (int i = count; i > 0; --i) {
        if (table[i][k] != table[i - 1][k]) {
            ++ans;
            k -= weights[i - 1];
        }
    }

    for (int i = 0; i <= count; ++i) {
        free(table[i]);
    }
    free(table);
    return ans;
}

int main() {
  int res;
  int capacity;
  int * weights;
  int count;

  res = scanf("%d", &capacity);
  assert(res == 1);

  count = read_weights(&weights);
  if (count == -1){
    free(weights);
  }
  if (count < 1){
    return 1;
  }

  res = knapsack(capacity, weights, count);
  printf("%d\n", res);

  free(weights);
}
