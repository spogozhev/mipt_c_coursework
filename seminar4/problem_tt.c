#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};


struct tree_t *create_node(int data, struct tree_t *left, struct tree_t *right);
void print_pre(struct tree_t *top);
void print_in(struct tree_t *top);
void print_post(struct tree_t *top);
void free_tree(struct tree_t *top);
struct tree_t *createTree(int* preorder, int* inorder, int n);

int main() {
    int res;
    int n;
    int * preorder;
    int * inorder;
    struct tree_t *top;
    int i;

    res = scanf("%d", &n);
    assert(res == 1);
    assert(n > 0);

    preorder = (int*)calloc(n, sizeof(int));
    assert(preorder != NULL);
    for (i = 0; i < n; ++i) {
        res = scanf("%d", preorder + i);
        assert(res == 1);
    }

    inorder = (int*)calloc(n, sizeof(int));
    assert(inorder != NULL);
    for (i = 0; i < n; ++i) {
        res = scanf("%d", inorder + i);
        assert(res == 1);
    }

    top = createTree(preorder, inorder, n);

#if 0
    // print preorder
    printf("pre: ");
    print_pre(top);
    printf("\n");

    // print inorder
    printf("in: ");
    print_in(top);
    printf("\n");
      // print postorder
    printf("post: ");
#endif
    print_post(top);
    printf("\n");

    // free everything
    free_tree(top);
    free(inorder);
    free(preorder);
}

#line 10000

struct tree_t *create_node(int data, struct tree_t *left, struct tree_t *right) {
  struct tree_t *ret = (struct tree_t*)malloc(sizeof(struct tree_t));
  assert(ret);

  ret->left = left;
  ret->right = right;
  ret->data = data;
  return ret;
}

void print_pre(struct tree_t *top){
    if (top == NULL){
        return;
    }
    printf("%d ", top->data);
    print_pre(top->left);
    print_pre(top->right);    
}

void print_in(struct tree_t *top){
    if (top == NULL){
        return;
    }
    print_in(top->left);
    printf("%d ", top->data);
    print_in(top->right);    
}

void print_post(struct tree_t *top){
    if (top == NULL){
        return;
    }
    print_post(top->left);
    print_post(top->right);    
    printf("%d ", top->data);
}

void free_tree(struct tree_t *top) {
  if (top == NULL)
    return;
  free_tree(top->left);
  free_tree(top->right);
  free(top);
}

int atArray(int* arr, int from, int to, int value) {
    int i;
    for (i = from; i <= to; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

struct tree_t* createTreeRecur(int* preorder, int* inorder, int *preIndex, int from, int to) {
    struct tree_t* root;
    int index;
    if (from > to) {
        return NULL;
    }
    root = create_node(preorder[*preIndex], NULL, NULL);
    ++(*preIndex);
    
    index = atArray(inorder, from, to, preorder[(*preIndex) - 1]);
    root->left = createTreeRecur(preorder, inorder, preIndex, from, index - 1);
    root->right = createTreeRecur(preorder, inorder, preIndex, index+1, to);
    return root;
}

struct tree_t* createTree(int* preorder, int* inorder, int n) {
    int preIndex = 0;
    return createTreeRecur(preorder, inorder, &preIndex, 0, n - 1);
}
