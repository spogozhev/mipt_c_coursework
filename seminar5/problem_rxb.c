#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
  regex_t regex;
  int res;
  char buffer[256];

  res = scanf("%s", buffer);
  const char * cregex = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"; 
  //const char * cregex = "^([^\\.][\\w\\.\\-]+)@([\\w\\-]+)((\\.(\\w){2,})+)$";
  
  regcomp(&regex, cregex, REG_EXTENDED);
  res = regexec(&regex, buffer, 0, NULL, 0);
  if (res == 0){
    printf("1");
  }else {
    printf("0");
  }

  regfree(&regex);

  return 0;
}
