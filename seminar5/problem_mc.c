// + https://education.yandex.ru/handbook/algorithms/article/zadacha-razmen-2
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 }

int read_nominals(int **nominals){
    int res;
    int count;
    res = scanf("%d", &count);
    if (res != 1){
        nominals = NULL;
        return 0;
    }
    *nominals = (int *)calloc(count, sizeof(int));
    if (nominals == NULL){
        return 0;
    }
  
    for(int i = 0; i < count; ++i) {
        res = scanf("%d", (*nominals) + i);
        if (res!=1){
            return -1;
        }
    }
    qsort(*nominals, count, sizeof(int), compare_ints);
    return count;
}

int mymin(int x, int y) {
    return x < y ? x : y;
}

int change(int sum, const int * nominals, int count){
    int ans = 0;
    int * table = (int *)calloc(sum + 1, sizeof(int));
    assert(table != NULL);
    for (int i = 0; i <= sum; ++i){
        table[i] = sum * 10;
    }
    
    table[0] = 0;
    for (int m = 1; m <= sum; ++m) {
	    for (int index = 0; index < count; ++index) {
		    if (nominals[index] <= m) {
			    table[m] = mymin(table[m], 1 + table[m - nominals[index]]);
		    }
	    }
    }
    ans = table[sum];
    free(table);
    return ans;
}

int main() {
  int res;
  int sum;
  int * nominals;
  int count;

  res = scanf("%d", &sum);
  assert(res == 1);

  count = read_nominals(&nominals);
  if (count == -1){
    free(nominals);
  }
  if (count < 1){
    return 1;
  }

  res = change(sum, nominals, count);
  printf("%d\n", res);
  free(nominals);
}
