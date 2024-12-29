#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void multMatrixRight(const unsigned A[], unsigned B[], unsigned m){
    // B = A * B
    unsigned tmp[4];
    tmp[0] = ((A[0]*B[0])%m + (A[1]*B[2])%m)%m;
    tmp[1] = ((A[0]*B[1])%m + (A[1]*B[3])%m)%m;
    tmp[2] = ((A[2]*B[0])%m + (A[3]*B[2])%m)%m;
    tmp[3] = ((A[2]*B[1])%m + (A[3]*B[3])%m)%m;

    B[0] = tmp[0];
    B[1] = tmp[1];
    B[2] = tmp[2];
    B[3] = tmp[3];
}

int main() {
  unsigned matrix[4] = {0, 0, 0, 0};
  unsigned n = 0;
  unsigned m = 0;
  int res;

  res = scanf("%d %d %d %d", &matrix[0], &matrix[1], &matrix[2], &matrix[3]);
  assert(res == 4);
  res = scanf("%d %d", &n, &m);
  assert(res == 2);
  
  unsigned prod[4] = {1, 0, 0, 1};

  while ( n > 0 ){
       if ((n%2) == 1){
            multMatrixRight(matrix, prod, m);
            --n;
        }
        multMatrixRight(matrix, matrix, m);
        n /= 2; // n >>= 1;
  }

  printf("%u %u %u %u", prod[0], prod[1], prod[2], prod[3]);
  return 0;
}
