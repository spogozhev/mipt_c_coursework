#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string{
  char * str;
  int length;  
};

void reverse(char *str, int len);
int read_str(struct string *str);
void reverse_words(struct string *where, struct string const *what);

int main() {
  struct string what;
  struct string where;
  int res;

  res = read_str(&what);
  if (res==0){
    return 0;
  }
  res = read_str(&where);
  if (res==0){
    free(what.str);
    return 0;
  }

  reverse_words(&where, &what);
  printf("%s\n", where.str);

  free(where.str);
  free(what.str);
  return 0;
}

void reverse(char *str, int len){
  char ch;
  for(int i=0, j=len-1; i<j; ++i, --j){
    ch = str[i];
    str[i] = str[j];
    str[j] = ch;
  }
}

int read_str(struct string *str){
  int size;
  int res;
  char ch;
  int i;
  res = scanf("%d", &size);
  if (res!=1){
    return 0;
  }
  res = scanf("%c", &ch);
  str->str = (char*) calloc(size+1, sizeof(char));
  if (str->str==NULL){
    str->length = 0;
    return 0;
  }
  str->length = size;
  for(i = 0; i < size; ++i){
    res = scanf("%c", &ch);
    if (res!=1){
      return 0;
    }
    str->str[i] = ch;
  }
  return 1;
}

void reverse_words(struct string *where, struct string const *what){
  char * last = where->str;
  while((last=strstr(last, what->str))!=NULL){
    reverse(last, what->length);
    last += what->length;
  }
}