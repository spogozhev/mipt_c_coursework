#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 0;
    int element;
    int minimum = 0;
    int maximum = 0;
    int res;

    res = scanf("%d", &N);
    assert(res == 1);

    if (N>0){
        scanf("%d", &minimum);
        maximum = minimum;
        for(int i = 1; i<N; ++i){
            scanf("%d", &element);
            if (element > maximum){
                maximum = element;
            }else if (element < minimum){
                minimum = element;
            }
        }
    }

    printf("%d %d", minimum, maximum);
    return 0;
}

