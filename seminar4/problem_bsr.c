#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct buckets_t{
    int size;
    struct node_t ** data;    
};

struct buckets_t create_buckets(int *arr, int n);
void print_list(struct node_t *top);
void delete_list(struct node_t *top);
void delete_buckets(struct buckets_t *buckets);

int main() {
  int res, n, i, answ;
  int *arr;
  struct buckets_t buckets;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  arr = (int*)calloc(n, sizeof(int));
  assert(arr != NULL);
  for (i = 0; i < n; ++i) {
    res = scanf("%d", arr + i);
    assert(res == 1);
  }

  buckets = create_buckets(arr, n);

  for (i = 0; i < n; ++i) {
    print_list(buckets.data[i]);
    printf("0 ");
  }

  delete_buckets(&buckets);
  free(arr);
  return 0;
}

struct buckets_t create_buckets(int *arr, int n){
    struct buckets_t buckets;
    struct node_t *tmp;
    struct node_t *cur;
    struct node_t *prev;
    int i, k;
    int maxval;

    buckets.size = n;
    buckets.data = NULL;
    if (n==0){
        return buckets;
    }

    buckets.data = (struct node_t **)calloc(n, sizeof(struct node_t *));
    assert(arr != NULL);
    
    maxval = arr[0];
    for(i = 1; i < n; ++i){
        if (arr[i] > maxval){
            maxval = arr[i];
        }
    }
    maxval /= n;
    for(i = 0; i < n; ++i){
        k = arr[i] / maxval;
        k = (k>n-1) ? n-1 : k;
        if (buckets.data[k] == NULL){
            buckets.data[k] = (struct node_t *) malloc(sizeof(struct node_t));
            buckets.data[k]->next = NULL;
            buckets.data[k]->data = arr[i];
        } else {
            tmp = (struct node_t *) malloc(sizeof(struct node_t));
            tmp->data = arr[i];
            prev = NULL;
            cur = buckets.data[k];
            while(cur!=NULL && cur->data <= arr[i]){
                prev = cur;
                cur = cur->next;
            }
            if (prev == NULL){
                tmp->next = buckets.data[k];
                buckets.data[k] = tmp;
            } else {
                tmp->next = prev->next;
                prev->next = tmp;
            }
        }
    }

    return buckets;
}

void delete_list(struct node_t *top){
  struct node_t *cur;
  while(top != NULL){
    cur = top;
    top = top->next;
    free(cur);
  }
}

void delete_buckets(struct buckets_t *buckets){
    int i;
    for(i = 0; i < buckets->size; ++i){
        if (buckets->data[i] != NULL){
            delete_list(buckets->data[i]);
        }
    }
    free(buckets->data);
    buckets->data = NULL;
    buckets->size = 0;
}

void print_list(struct node_t *top){
    struct node_t *cur;
    cur = top;
    while (cur!=NULL){
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

