#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 0;
    unsigned *ar;
    int shift;
    int index = 0;    
    int res;

    res = scanf("%d", &N);
    assert(res == 1);
    assert(N > 0);


    ar = (unsigned *) malloc(N*sizeof(unsigned));
    for(int i = 0; i<N; ++i){
        scanf("%u", &(ar[i]));
    }

    res = scanf("%d", &shift);
    index = 0;
    while( (shift>8) && (index<N)){
        shift -= 8;
        ++index;
    }
    if (index<N){
        ar[index] = ar[index] ^ (1<<shift);
    }

    for(int i = 0; i<N; ++i){
        printf("%u ", ar[i]);
    }

    free(ar);
    return 0;
}

