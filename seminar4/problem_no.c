#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

struct stacknode{
    struct stacknode * next;
    struct tree_t * data;
};

struct tree_t *create_node(int data, struct tree_t *l, struct tree_t *r);
void insert(struct tree_t **root, int val);
struct tree_t* readfile(FILE *f);
void free_tree(struct tree_t *top);
void print_pre(struct tree_t *top);

int main() {
  struct tree_t * top;

  // read tree from file
  top = readfile(stdin);

  // print preorder
  print_pre(top);
  printf("\n");

  // free everything
  free_tree(top);
}

#line 10000

struct tree_t *create_node(int data, struct tree_t *l, struct tree_t *r) {
  struct tree_t *ret = (struct tree_t *)malloc(sizeof(struct tree_t));
  assert(ret);

  ret->left = l;
  ret->right = r;
  ret->data = data;
  return ret;
}

void insert(struct tree_t **root, int val){
    struct tree_t * cur;
    struct tree_t * parent;
    if (*root == NULL){
        *root = create_node(val, NULL, NULL);
        return;
    }
    
    cur = *root;
    while(cur != NULL){
        parent = cur;
        if (val < cur->data){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    if (val < parent->data){
        parent->left = create_node(val, NULL, NULL);
    } else{
        parent->right = create_node(val, NULL, NULL);
    }
}

void free_tree(struct tree_t *top) {
  if (top == NULL)
    return;
  free_tree(top->left);
  free_tree(top->right);
  free(top);
}

struct tree_t* readfile(FILE *f) {
  struct tree_t *ans;
  int res, n, i, val;

  res = fscanf(f, "%d", &n);
  assert(res == 1);
  
  ans = NULL;
  for (i = 0; i < n; ++i) {
    res = fscanf(f, "%d", &val);
    assert(res == 1);
    insert(&ans, val);
  }

  return ans;
}


void push (struct stacknode ** stack, struct tree_t * data){
    struct stacknode *tmp = (struct stacknode *)calloc(1, sizeof(struct stacknode));
    tmp->data = data;
    tmp->next = *stack;
    *stack = tmp;
}

struct tree_t * pop (struct stacknode ** stack){
    struct tree_t *data = (*stack)->data;
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

void print_pre(struct tree_t *top){
    struct stacknode * stack = NULL;
    struct tree_t * cur;
    if (top == NULL){
        return;
    }
    push(&stack, top);
    while(stack!=NULL){
        cur = pop(&stack);
        printf("%d ", cur->data);
        if (cur->right != NULL){
            push(&stack, cur->right);
        }
        if (cur->left != NULL){
            push(&stack, cur->left);
        }
    }
}