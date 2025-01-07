#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//                                        {5, 3, 4}
const int mt[5][3]={{1, 2, 5}, {1, 2, 3}, {5, 4, 3}, {5, 4, 3}, {5, 5, 5}};
int isfinal(int state){
    return  (state==2 || state==3 || state==4);
}

int fsm(){
    char ch;
    int res;
    int state = 1;
    for(;;){
        res = scanf("%c", &ch);
        if (res!=1 || (ch<'a') || (ch>'c')){
            break;
        }
        state = mt[state-1][ch-'a'];
    }
    return isfinal(state);
}

int main() {
  int res;

  res = fsm();

  printf("%d\n", res);

  return 0;
}
