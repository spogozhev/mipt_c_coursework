#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMinrun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r; // minrun
}

void insertionSort(int* arr[], int left, int right, int X) { 
    int * temp;
    int key;
    int i, j;
    for (i = left + 1; i <= right; i++) { 
        temp = arr[i]; 
        key = temp[X];
        j = i - 1; 
        while ( (j >= left) && (key < arr[j][X]) ) { 
            arr[j + 1] = arr[j]; 
            --j; 
        } 
        arr[j + 1] = temp; 
    } 
} 

void merge(int* arr[], int left, int middle, int right, int X) { 
    int **arrLeft;
    int **arrRight; 
    int lenLeft = middle - left + 1;
    int lenRight = right - middle; 
    int i, j, k;
    arrLeft = (int**)calloc(lenLeft, sizeof(int*));
    assert(arrLeft != NULL);
    arrRight = (int**)calloc(lenRight, sizeof(int*));
    assert(arrRight != NULL);

    // memcpy(aleft, arr, len1*sizeof(int*));
    for (i = 0; i < lenLeft; i++){ 
        arrLeft[i] = arr[left + i]; 
    }
    // memcpy(aright, arr+middle+1, len2*sizeof(int*));
    for (i = 0; i < lenRight; i++){
        arrRight[i] = arr[middle + 1 + i]; 
    }

    i = 0; 
    j = 0; 
    k = left; 
  
    while (i < lenLeft && j < lenRight) { 
        if (arrLeft[i][X] <= arrRight[j][X]) { 
            arr[k] = arrLeft[i]; 
            ++i; 
        } 
        else { 
            arr[k] = arrRight[j]; 
            ++j; 
        } 
        ++k; 
    } 
  
    while (i < lenLeft) { 
        arr[k] = arrLeft[i]; 
        k++; 
        i++; 
    } 
  
    while (j < lenRight) { 
        arr[k] = arrRight[j]; 
        k++; 
        j++; 
    } 
    free(arrLeft);
    free(arrRight);
} 

void timSort(int** arr, int N, int K, int X){
    int minrun;
    int size;
    int i;
    int left, middle, right;
    minrun = getMinrun(N);
    // printf("minrun: %d\n", minrun);
    // Sort subarrays of size "minrun" 
    for (i = 0; i < N; i += minrun){
        size = i + minrun - 1;
        size = (size < N-1) ? size : (N - 1);
        insertionSort(arr, i, size, X); 
    }

    // Start merging from size minrun. 
    for (size = minrun; size < N; size = 2 * size) { 
        // Merge  arr[left ... left+size-1] 
        // and    arr[left+size ... left+2*size-1] 
        for (left = 0; left < N; left += 2 * size) { 
            middle = left + size - 1; 
            right = left + 2 * size - 1;
            right = (right < N-1) ? right : (N-1); 
            if (middle < right){
                merge(arr, left, middle, right, X); 
            }
        } 
    } 
}

int main() {
  int res;
  int N, K, X;
  int ** arr;
  int i, j;
  res = scanf("%d%d%d", &N, &K, &X);
  assert(res == 3);
  assert(N > 0);
  assert(K > 0);  

  arr = (int**)calloc(N, sizeof(int*));
  assert(arr != NULL);
  for (i = 0; i < N; ++i) {
    arr[i] = (int*)calloc(K, sizeof(int));
    assert(arr[i] != NULL);
    for(j=0; j < K; ++j){
        res = scanf("%d", arr[i] + j);
        assert(res == 1);
    }
  }

  timSort(arr, N, K, X);

  for (i = 0; i < N; ++i){
    printf("%d ", arr[i][i%K]);
  }

  for (i = 0; i < N; ++i) {
    free(arr[i]);
  }
  free(arr);
  
  return 0;
}
