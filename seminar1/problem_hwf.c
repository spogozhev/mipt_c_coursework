#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int next_turn(int total, int possible);

int main()
{
    int n, q, res;

    res = scanf("%d%d", &n, &q);
    assert(res == 2);

    n = next_turn(n, q);
    printf("%d\n", n);

    return 0;
}

int next_turn(int total, int possible){
    int fibNumbers[2] = {1, 2};
    int result = 1;
    int tmp;

    if (total <= possible){
        return total;
    }

    while( fibNumbers[1] < total ){
        tmp = (fibNumbers[0] + fibNumbers[1]);
        fibNumbers[0] = fibNumbers[1];
        fibNumbers[1] = tmp;
    }

    while(fibNumbers[1] >= 2){
        if (total >= fibNumbers[0]){
            total -= fibNumbers[0];
            if (fibNumbers[0] < possible){
                result = fibNumbers[0];
            }
        }
        tmp = fibNumbers[1] - fibNumbers[0];
        fibNumbers[1] = fibNumbers[0];
        fibNumbers[0] = tmp;
    }
    return result;
}
