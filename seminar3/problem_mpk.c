#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void karatsuba(int *a, int *b, int *c, int n) {
    // c(x) = a(x) * b(x)

    if (n <= 32) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c[i + j] += a[i] * b[j];
    }
    else {
        int k = n / 2;
        int *left = (int*)calloc(k, sizeof(int));
        int *right = (int*)calloc(k, sizeof(int));
        int *t = (int*)calloc(n, sizeof(int));

        for (int i = 0; i < k; i++) {
            left[i] = a[i] + a[k + i];
            right[i] = b[i] + b[k + i];
        }
        karatsuba(left, right, t, k); // calc t(x)
        free(left);
        free(right);        
        karatsuba(a, b, c, k); // calc p_1(x) = a_1(x) * b_1(x)
        karatsuba(a + k, b + k, c + n, k); // calc p_2(x) = a_2(x) * b_2(x)
        int *t1 = t, *t2 = t + k;
        int *s1 = c, *s2 = c + k, *s3 = c + 2 * k, *s4 = c + 3 * k;
        for (int i = 0; i < k; i++) {
            int c1 = s2[i] + t1[i] - s1[i] - s3[i];
            int c2 = s3[i] + t2[i] - s2[i] - s4[i];
            c[k + i] = c1;
            c[n + i] = c2;
        }
        free(t);
    }
}

int main() {
  int res;
  int i;
  int maxdeg;
  int deg1;
  int deg2;
  int deg3;
  int * pol1;
  int * pol2;
  int * pol3;

  res = scanf("%d%d", &deg1, &deg2);
  assert(res == 2);
  assert(deg1 > 0);
  assert(deg1 == deg2);  

  pol1 = (int*)calloc(deg1, sizeof(int));
  assert(pol1 != NULL);
  for (i = 0; i < deg1; ++i) {
    res = scanf("%d", pol1 + i);
    assert(res == 1);
  }

  pol2 = (int*)calloc(deg2, sizeof(int));
  assert(pol2 != NULL);
  for (i = 0; i < deg2; ++i) {
    res = scanf("%d", pol2 + i);
    assert(res == 1);
  }
  deg3 = deg1 + deg2 - 1;
  pol3 = (int*)calloc(deg3, sizeof(int));
  assert(pol3 != NULL);  

  karatsuba(pol1, pol2, pol3, deg1);
  maxdeg = deg3;
  while(maxdeg>0 && pol3[maxdeg-1]==0){
    --maxdeg;
  }
  
  for (i = 0; i < maxdeg; ++i)
    printf("%d ", pol3[i]);

  free(pol1);
  free(pol2);
  free(pol3);
  return 0;
}
