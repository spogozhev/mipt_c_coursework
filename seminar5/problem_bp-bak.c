// + https://education.yandex.ru/handbook/algorithms/article/zadacha-o-ryukzake
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int read_weights(int **weights){
    int res;
    int count;
    res = scanf("%d", &count);
    if (res != 1){
        weights = NULL;
        return 0;
    }
    *weights = (int *)calloc(count, sizeof(int));
    if (weights == NULL){
        return 0;
    }
  
    for(int i = 0; i < count; ++i) {
        res = scanf("%d", (*weights) + i);
        if (res!=1){
            return -1;
        }
    }
    return count;
}

struct pair{
    int key;
    int value;
};

int is_equal(struct pair x, struct pair y){
    if (x.key==y.key && x.value==y.value){
        return 1;
    }
    return 0;
}

struct node {
    struct node * next;
    struct pair data;
    int tf;
};

struct hash_table {
    int size;
    struct list_node** table;
};

int hash(struct pair data){
    return 101 * data.key + 293 * data.value;
}

struct hash_table * create_hash_table(int size){
    struct hash_table* ht = (struct hash_table*)calloc(1, sizeof(struct hash_table));
    ht->size = size;
    ht->table = (struct list_node**)calloc(size, sizeof(struct list_node*));
    for(int i=0; i<size; ++i){
        ht->table[i] = NULL;
    }
    return ht;
}

void delete_list(struct node * first){
    struct node *cur;
    while(first != NULL){
        cur = first;
        first = first->next;
        free(cur);
    }
}

void delete_hash_table(struct hash_table* ht){
    for(int i=0; i < ht->size; ++i){
        delete_list(ht->table[i]);
    }
    free(ht->table);
    ht->table = NULL;
    ht->size = 0;
}

struct node* insert_list(struct node* first, struct pair data, int tf){
    struct node* cur = (struct node*)calloc(1, sizeof(struct node));
    cur->data = data;
    cur->tf = tf;
    cur->next = first;
    return cur;
}

void insert_hash_table(struct hash_table* ht, struct pair data, int tf){
    int index = hash(data) % ht->size; 
    insert_list(ht->table[index], data, tf);
}

int at_list(struct node* first, struct pair data){
    struct node * cur = first;
    while( cur != NULL){
        if (is_equal(cur->data, data)) {
            return 1;
        }
    }
    return 0;
}

int at_hash_table(struct hash_table* ht, struct pair data){
    int index = hash(data) % ht->size; 
    return at_list(ht->table[index], data);
}

int get_tf_list(struct node* first, struct pair data){
    struct node * cur = first;
    while( cur != NULL){
        if (is_equal(cur->data, data)) {
            return cur->tf;
        }
    }
    assert(1==0);
    return -1;
}

int get_tf(struct hash_table* ht, struct pair data){
    int index = hash(data) % ht->size; 
    return get_tf_list(ht->table[index], data);
}


int knapsack(int capacity, int i, int * weights, int count, struct hash_table* pack) {
    struct pair data;
    int tmp1, tmp2;
    data.key = capacity;
    data.value = i;
    if (at_hash_table(pack, data)==0){ // (w,i) is not in pack
        if (i==0 && capacity==0){
            insert_hash_table(pack, data, 1);
        } else if (i==0 && capacity > 0){
            insert_hash_table(pack, data, 0);
        } else if (i>0 && weights[i-1] > capacity){
            insert_hash_table(pack, data, knapsack(capacity, i-1, weights, count, pack));
        } else if (i > 0){
            tmp1 = knapsack(capacity, i-1, weights, count, pack);
            tmp2 = knapsack(capacity, i-1, weights - weights[i-1], count, pack);
            tmp1 = (tmp2 > tmp1) ? tmp2 : tmp1;
            insert_hash_table(pack, data, tmp1);
        }
    }
    return get_tf(pack, data);
}

int main() {
  int res;
  int capacity;
  int * weights;
  int count;
  struct hash_table* pack;

  count = read_weights(&weights);
  if (count == -1){
    free(weights);
  }
  if (count < 1){
    return 1;
  }

  res = scanf("%d", &capacity);
  assert(res == 1);
  pack = create_hash_table(1001);

  res = knapsack(capacity, count, weights, count, pack);

  struct pair data;
  data.key = capacity;

  res = 0;
  for(int i=0; i < count; ++i){
    data.value = i;
    if (at_hash_table(pack, data)==1){
        ++res;
    }
  }
  
  printf("%d\n", res);

  free(weights);
  delete_hash_table(pack);
  free(pack);
}
