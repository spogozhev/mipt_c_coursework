#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *read_list(FILE *inp);
void delete_list(struct node_t *top);

int main() {
  struct node_t *top = read_list(stdin);
  struct node_t *cur = top;

  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");

  delete_list(top);
}

struct node_t *read_list(FILE *inp){
  struct node_t * even_begin = NULL;
  struct node_t * even_end = NULL;
  struct node_t * odd_begin = NULL;
  struct node_t * odd_end = NULL;
  int i;
  int res;
  while(!feof(inp)){
    res = fscanf(inp, "%d", &i);
    if (res==1){
      if (i%2==0){
        if (even_begin == NULL){
          even_begin = (struct node_t *) malloc(sizeof(struct node_t));
          even_end = even_begin;
        } else {
          even_end->next = (struct node_t *) malloc(sizeof(struct node_t));
          even_end = even_end->next;
        }
        even_end->data = i;
        even_end->next = NULL;
      } else {
        if (odd_begin == NULL){
          odd_begin = (struct node_t *) malloc(sizeof(struct node_t));
          odd_end = odd_begin;
        } else {
          odd_end->next = (struct node_t *) malloc(sizeof(struct node_t));
          odd_end = odd_end->next;
        }
        odd_end->data = i;
        odd_end->next = NULL;
      }
    }
  }
  fclose(inp);

  if (even_begin == NULL){
    return odd_begin;
  }
  even_end->next = odd_begin;
  return even_begin;
}

void delete_list(struct node_t *top){
  struct node_t *cur;
  while(top != NULL){
    cur = top;
    top = top->next;
    free(cur);
  }
}
