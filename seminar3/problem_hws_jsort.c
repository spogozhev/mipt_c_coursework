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

void shift_down_left(int* M[], int size, int pos, int X) {
    int* tmp;
	int posMaxChild;
	while ((posMaxChild = 2 * pos + 1) < size) { // Пока есть элемент слева
		if (posMaxChild + 1 < size) { // Есть ещё кто-то справа
			if (M[posMaxChild][X] > M[posMaxChild + 1][X]) {
				++posMaxChild;
			}
		}
		if (M[pos][X] > M[posMaxChild][X]) {
            tmp = M[pos];
            M[pos] = M[posMaxChild];
            M[posMaxChild] = tmp;
			pos = posMaxChild;
		}
		else break;
	}
}

void shift_down_right(int* M[], int size, int pos, int X) {
    int* tmp;
	int posMaxChild;
	while ((posMaxChild = 2 * pos + 1) < size) { // Пока есть элемент слева
		if (posMaxChild + 1 < size) { // Есть ещё кто-то справа
			if (M[size-1-posMaxChild][X] < M[size-1-(posMaxChild + 1)][X]) {
				++posMaxChild;
			}
		}
		if (M[size-1-pos][X] < M[size-1-posMaxChild][X]) {
            tmp = M[size-1-pos];
            M[size-1-pos] = M[size-1-posMaxChild];
            M[size-1-posMaxChild] = tmp;
            pos = posMaxChild;
		}
		else break;
	}
}

void jSort(int* arr[], int left, int right, int X){
    int size = right-left+1;
	for (int i = (right-left) / 2; i > 0; --i) {
		shift_down_left(arr+left, size, i-1, X);
	}

	for (int i = (right-left) / 2; i <size; ++i) {
		shift_down_right(arr+left, size, i-1, X);
	}

}

void insertionSort(int* arr[], int left, int right, int X) { 
    for (int i = left + 1; i <= right; i++) { 
        int* temp = arr[i]; 
        int key = temp[X];
        int j = i - 1; 
        while (j >= left && arr[j][X] > key) { 
            arr[j + 1] = arr[j]; 
            j--; 
        } 
        arr[j + 1] = temp; 
    } 
} 

void merge(int* arr[], int left, int middle, int right, int X) { 
    int len1 = middle - left + 1;
    int len2 = right - middle; 
    int **aleft;
    int **aright; 
    aleft = (int**)calloc(len1, sizeof(int*));
    aright = (int**)calloc(len2, sizeof(int*));
    for (int i = 0; i < len1; i++){ 
        aleft[i] = arr[left + i]; 
    }
    // memcpy(aleft, arr, len1*sizeof(int*));
    for (int i = 0; i < len2; i++){
        aright[i] = arr[middle + 1 + i]; 
    }
    // memcpy(aright, arr+middle+1, len2*sizeof(int*));

    int i = 0; 
    int j = 0; 
    int k = left; 
  
    while (i < len1 && j < len2) { 
        if (aleft[i][X] <= aright[j][X]) { 
            arr[k] = aleft[i]; 
            i++; 
        } 
        else { 
            arr[k] = aright[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < len1) { 
        arr[k] = aleft[i]; 
        k++; 
        i++; 
    } 
  
    while (j < len2) { 
        arr[k] = aright[j]; 
        k++; 
        j++; 
    } 
} 

void timSort(int** arr, int N, int K, int X){
    int minrun;
    int size;
    minrun = getMinrun(N);
    minrun = 128;
    printf("minrun: %d\n", minrun);
    // Sort subarrays of size "minrun" 
    for (int i = 0; i < N; i += minrun){
        size = i + minrun - 1;
        size = (size < N-1) ? size : (N - 1);
        jSort(arr, i, size, X); 
        insertionSort(arr, i, size, X); 
    }

    // Start merging from size minrun. 
    for (int size = minrun; size < N; size = 2 * size) { 
        // Merge  arr[left ... left+size-1] 
        // and    arr[left+size ... left+2*size-1] 
        for (int left = 0; left < N; left += 2 * size) { 
            int middle = left + size - 1; 
            int right = left + 2 * size - 1;
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
  float startTime, endTime, timeElapsed;
  startTime = (float)clock()/CLOCKS_PER_SEC;
  timSort(arr, N, K, X);
  endTime = (float)clock()/CLOCKS_PER_SEC;  
  timeElapsed = endTime - startTime;
  printf("time elapsed: %f\n", timeElapsed);
  for (i = 0; i < N; ++i){
    printf("%d ", arr[i][i%K]);
  }

  for (i = 0; i < N; ++i) {
    free(arr[i]);
  }
  free(arr);
  
  return 0;
}
