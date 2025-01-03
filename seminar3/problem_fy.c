#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int myrand() {
  static unsigned long int seed = 1;
  seed = seed * 1103515245 + 12345;
  return (unsigned int)(seed / 65536) % 32768;
}

void FisherYatesShuffle(int* ar, int size){
    int tmp;
    int index;
    
    for(int i=size-1; i>0; --i){
        index = myrand()%(i+1);
        tmp = ar[index];
        ar[index] = ar[i] ;
        ar[i] = tmp;
    }
}

int main() {
    int N = 0;
    int* ar;
    int i;
    int res;

    res = scanf("%d", &N);
    assert(res == 1);
    if (N==0){
        printf("0");
        return 0;
    }
    ar = (int *) malloc(N*sizeof(int));
    for(i=0; i<N; ++i){
        scanf("%d", &(ar[i]));
    }
    FisherYatesShuffle(ar, N);
    for(i=0; i<N; ++i){
        printf("%d ", ar[i]);
    }

    free(ar);
    return 0;
}

