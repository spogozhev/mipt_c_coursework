#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
  struct node_t *next;
  int data;
};

int loop_len(struct node_t *top);

int main() {
  int i, nnodes, looppos, res, outcome;
  struct node_t *top = NULL, *cur = NULL, *loopelem = NULL;

  res = scanf("%d%d", &nnodes, &looppos);
  assert(res == 2);
  assert(nnodes >= 0);
  assert(looppos > -2);
  assert(looppos < nnodes);

  if (nnodes > 0) {
    top = (struct node_t*)calloc(1, sizeof(struct node_t));
    cur = top;
    if (looppos == 0)
      loopelem = cur;
  }

  for (i = 1; i < nnodes; ++i) {
    cur->next = (struct node_t*)calloc(1, sizeof(struct node_t));
    if (looppos == i)
      loopelem = cur;
    cur = cur->next;
  }

  if (looppos != -1)
    cur->next = loopelem;

  outcome = loop_len(top);
  printf("%d\n", outcome);
}

int loop_len(struct node_t *top){
    struct node_t *slow = top;
    struct node_t *fast = top;
    int len;
    while((fast!=NULL) && (fast->next != NULL)){
        slow = slow->next;
        fast = fast->next->next;
        if (slow==fast){
            break;
        }
    }
    if ((fast == NULL) || (fast->next == NULL)){
        return 0;
    }
    
    /*
    // Search start of cicle
    slow = top;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    */
    // Cicle starts at fast
    len = 0;
    do{
        ++len;
        slow = slow->next;
    }while(slow != fast);

    return len;
}