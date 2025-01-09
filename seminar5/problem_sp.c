#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *str, char const *from, char const *to);

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  scanf("%*c");

  for (i = 0; i < n; ++i) {
    res = scanf("%c", text + i);
    assert(res == 1);
  }

  return text;
}

int main() {
  int i, nword, nrepl, nstr, res;
  char *word, *repl, *str, *newstr;

  word = read_word(&nword);
  repl = read_word(&nrepl);
  str = read_word(&nstr);

  newstr = replace(str, word, repl);

  printf("%s\n", newstr);

  free(word);
  free(repl);
  free(str);
  free(newstr);
}

char *replace(char *str, char const *from, char const *to){
    int len_from;
    int len_to;
    int count;
    int len_front;        
    char* last;
    char* tmp;
    char* result;
    if ( (str==NULL) || (from == NULL)){
        return NULL;
    }
    len_from = strlen(from);
    if (len_from == 0){
        return str;
    }
    if (to == NULL){
        to ="";
    }
    len_to = strlen(to);

    // count the number of needed replacements 
    last = str;
    for (count = 0; (tmp = strstr(last, from)); ++count) {
        last = tmp + len_from;
    }

    result = malloc(strlen(str) + count * (len_to - len_from) + 1);
    if (result == 0){
        return NULL;
    }
    tmp = result;
    while (count--) {
        last = strstr(str, from);
        len_front = last - str;
        tmp = strncpy(tmp, str, len_front) + len_front;
        tmp = strcpy(tmp, to) + len_to;
        str += len_front + len_from; // move to next
    }
    strcpy(tmp, str);
    return result;
}
