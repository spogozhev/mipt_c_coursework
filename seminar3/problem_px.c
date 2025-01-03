#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

void powNxN(unsigned (*A)[N], unsigned k, unsigned m);

int main() {
  int res, i, j;
  unsigned m, k;
  unsigned A[N][N];

  res = scanf("%u%u", &m, &k);
  assert(res == 2);
  assert(m > 0);

  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j) {
      res = scanf("%u", &A[i][j]);
      assert(res == 1);
    }

  powNxN(A, k, m);

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j)
      printf("%u ", A[i][j]);
    printf("\n");
  }
}

void multMatrixRight(const unsigned (*A)[N], unsigned (*B)[N], unsigned m){
    // B = A * B
    unsigned tmp[N][N] = {0};
    int i, j, k;
    for(i=0; i<N; ++i){
        for(j=0; j<N; ++j){
            for(k=0; k<N; ++k){
                tmp[i][j] += (A[i][k]*B[k][j])%m;
                tmp[i][j] %= m;
            }
        }
    }

    for(i=0; i<N; ++i){
        for(j=0; j<N; ++j){
            B[i][j] = tmp[i][j];
        }
    }
}

void powNxN(unsigned (*A)[N], unsigned k, unsigned m){
  unsigned prod[N][N] = {0};
  int i, j;
  for(i=0; i < N; ++i){
    prod[i][i] = 1;
  }

  while ( k > 0 ){
       if ((k%2) == 1){
            multMatrixRight(A, prod, m);
            --k;
        }
        multMatrixRight(A, A, m);
        k /= 2; // k >>= 1;
  }

  for(i=0; i < N; ++i){
    for(j=0; j < N; ++j){
        A[i][j] = prod[i][j];
    }
  }
}