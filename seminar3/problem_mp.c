#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct polynom{
    int deg;
    int* coef;
};

struct polynom mult(struct polynom pol1, struct polynom pol2){
    struct polynom pol3;
    int i, j;
    pol3.deg = pol1.deg + pol2.deg - 1;
    pol3.coef = (int*)calloc(pol3.deg, sizeof(int));
    for(i=0; i<pol1.deg; ++i){
        for(j=0; j<pol2.deg; ++j){
            pol3.coef[i+j] += pol1.coef[i]*pol2.coef[j];
        }
    }
    return pol3;
}

int main() {
  int res;
  int i;
  int maxdeg;
  struct polynom pol1;
  struct polynom pol2;
  struct polynom pol3;

  res = scanf("%d%d", &pol1.deg, &pol2.deg);
  assert(res == 2);
  assert(pol1.deg > 0);
  assert(pol2.deg > 0);

  pol1.coef = (int*)calloc(pol1.deg, sizeof(int));
  for (i = 0; i < pol1.deg; ++i) {
    res = scanf("%d", pol1.coef + i);
    assert(res == 1);
  }

  pol2.coef = (int*)calloc(pol2.deg, sizeof(int));
  for (i = 0; i < pol2.deg; ++i) {
    res = scanf("%d", pol2.coef + i);
    assert(res == 1);
  }
  
  pol3 = mult(pol1, pol2);
  maxdeg = pol3.deg;
  while(maxdeg>0 && pol3.coef[maxdeg-1]==0){
    --maxdeg;
  }
  
  for (i = 0; i < maxdeg; ++i)
    printf("%d ", pol3.coef[i]);

  free(pol1.coef);
  free(pol2.coef);
  free(pol3.coef);
  return 0;
}
