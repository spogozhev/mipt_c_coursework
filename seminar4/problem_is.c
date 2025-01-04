#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

struct tree_file_t {
  int n;
  int *topology; // 2 * n
  int *values;   // n
};

struct tree_file_t readfile(FILE *f) {
  struct tree_file_t ret;
  int res, i;

  res = fscanf(f, "%d", &ret.n);
  assert(res == 1);

  ret.topology = (int*)calloc(2 * ret.n, sizeof(int));
  ret.values = (int*)calloc(ret.n, sizeof(int));

  for (i = 0; i < 2 * ret.n; ++i) {
    res = fscanf(f, "%d", ret.topology + i);
    assert(res == 1);
  }

  for (i = 0; i < ret.n; ++i) {
    res = fscanf(f, "%d", ret.values + i);
    assert(res == 1);
  }

  return ret;
}

void free_temp(struct tree_file_t data) {
  free(data.topology);
  free(data.values);
}

void free_tree(struct tree_t *top) {
  if (top == NULL)
    return;
  free_tree(top->left);
  free_tree(top->right);
  free(top);
}

struct tree_t *create_node(int data, struct tree_t *l, struct tree_t *r) {
  struct tree_t *ret = (struct tree_t *)malloc(sizeof(struct tree_t));
  assert(ret);

  ret->left = l;
  ret->right = r;
  ret->data = data;
  return ret;
}

struct tree_t *do_recover(struct tree_file_t data, int *cursor, int *curval) {
  struct tree_t *n = NULL;
  int cur = *cursor;
  int curv = *curval;
  *cursor += 1;
  if (cur < (data.n * 2) && data.topology[cur] == 1) {
    struct tree_t *l, *r;
    *curval += 1;
    l = do_recover(data, cursor, curval);
    r = do_recover(data, cursor, curval);
    assert(curv < data.n);
    n = create_node(data.values[curv], l, r);
  }
  return n;
}

struct tree_t *recover(struct tree_file_t data) {
  int cursor = 0;
  int curval = 0;
  return do_recover(data, &cursor, &curval);
}

int check_is_bst(struct tree_t *top);

int main() {
  int is_search;
  struct tree_t *top;
  struct tree_file_t filetree;

  // read tree from file
  filetree = readfile(stdin);

  // recover tree
  top = recover(filetree);

  // check if search
  is_search = check_is_bst(top);

  printf("%d\n", is_search);

  // free everything
  free_tree(top);
  free_temp(filetree);
}

#line 10000

struct packet{
    struct tree_t * treenode;
    int from;
    int to;
};

struct stacknode{
    struct stacknode * next;
    struct packet data;
};

void push (struct stacknode ** stack, struct packet data){
    struct stacknode *tmp = (struct stacknode *)calloc(1, sizeof(struct stacknode));
    tmp->data = data;
    tmp->next = *stack;
    *stack = tmp;
}

struct packet pop (struct stacknode ** stack){
    struct packet data = (*stack)->data;
    struct stacknode *next = (*stack)->next;
    free(*stack);
    (*stack) = next;
    return data;
}

void delete_stack(struct stacknode ** stack){
    struct stacknode *next;
    while(*stack != NULL){
        next = (*stack)->next;
        free(*stack);
        (*stack) = next;
    }
}

int check_is_bst(struct tree_t *top){
    struct packet data;
    struct packet childdata;
    struct stacknode * stack = NULL;
    struct tree_t * cur;
    if (top == NULL){
        return 1;
    }
    data.treenode = top;
    data.from = INT_MIN;
    data.to = INT_MAX;
    push(&stack, data);
    while(stack!=NULL){
        data = pop(&stack);
        cur = data.treenode;
        if (cur->data < data.from || cur->data > data.to){
            delete_stack(&stack);
            return 0;
        }
        if (cur->right != NULL){
            childdata.treenode = cur->right;
            childdata.from = cur->data;
            childdata.to = data.to;
            push(&stack, childdata);
        }
        if (cur->left != NULL){
            childdata.treenode = cur->left;
            childdata.from = data.from;
            childdata.to = cur->data;
            push(&stack, childdata);
        }
    }
    return 1;
}
