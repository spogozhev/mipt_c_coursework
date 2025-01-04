#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMinrun(int n);
void insertionSort(int* arr, int left, int right);
void merge(int* arr, int left, int middle, int right);
void timSort(int* arr, int N);
int less(int* arr, int N, int x);
int lesseq(int* arr, int N, int x);

int main() {
  int res;
  int N;
  int * arr;
  int K;
  int left, right;
  int i, j;
  res = scanf("%d", &N);
  assert(res == 1);
  assert(N > 0);

  arr = (int*)calloc(N, sizeof(int));
  assert(arr != NULL);
  for (i = 0; i < N; ++i) {
        res = scanf("%d", arr + i);
        assert(res == 1);
  }

  timSort(arr, N);

  res = scanf("%d", &K);
  assert(res == 1);
  assert(N > 0);


  for (i = 0; i < K; ++i){
    res = scanf("%d%d", &left, &right);
    assert(res == 2);
#if 0
    int res1, res2;
    res1 = less(arr, N, left);
    res2 = lesseq(arr, N, right);
    printf("less %d-%d ", left, res1);
    printf(", less %d-%d\n", right, res2);
#else
    res = lesseq(arr, N, right) - less(arr, N, left);
    printf("%d ", res);
#endif    
  }

  free(arr);
 
  return 0;
}

int binSearch(int* arr, int N, int x){
    int left = 0;
    int right = N-1;
    int mid;
    while(left < right){
        mid = left + (right - left) / 2;
        if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right= mid;
        }
    }
    return right;
}

int less(int* arr, int N, int x){
    int res;
    res = binSearch(arr, N, x);
    while(res >= 0 && arr[res] >= x){
        --res;
    }
    return (res<0) ? 0 : res + 1;
}

int lesseq(int* arr, int N, int x){
    int res;
    res = binSearch(arr, N, x);
    while(res < N && arr[res] <= x){
        ++res;
    }
    return res;
}

int getMinrun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r; // minrun
}

void insertionSort(int* arr, int left, int right) { 
    int key;
    int i, j;
    for (i = left + 1; i <= right; i++) { 
        key = arr[i];
        j = i - 1; 
        while ( (j >= left) && (key < arr[j]) ) { 
            arr[j + 1] = arr[j]; 
            --j; 
        } 
        arr[j + 1] = key; 
    } 
} 

void merge(int* arr, int left, int middle, int right) { 
    int *arrLeft;
    int *arrRight; 
    int lenLeft = middle - left + 1;
    int lenRight = right - middle; 
    int i, j, k;
    arrLeft = (int*)calloc(lenLeft, sizeof(int));
    assert(arrLeft != NULL);
    arrRight = (int*)calloc(lenRight, sizeof(int));
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
        if (arrLeft[i] <= arrRight[j]) { 
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

void timSort(int* arr, int N){
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
        insertionSort(arr, i, size); 
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
                merge(arr, left, middle, right); 
            }
        } 
    } 
}
