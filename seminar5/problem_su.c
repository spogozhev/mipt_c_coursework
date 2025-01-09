#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned R = 10u;
const unsigned Q = 31u;

unsigned get_hash(const char *pat, const char *end);
unsigned update_hash(unsigned hash, unsigned n, char cf, char cl);
unsigned long long pow_mod(unsigned n, unsigned k, unsigned m);

char *strstrci(char const *needle, char const *haystack);

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
  int nlen, hlen, res;
  char *needle, *haystack, *sres;

  haystack = read_word(&hlen);
  needle = read_word(&nlen);

  sres = strstrci(needle, haystack);

  printf("%s\n", sres);

  free(haystack);
  free(needle);
}


// say hash(c1, c2, c3) = c1*r^2 + c2*r + c3
//                      = ((c1 * r + c2) * r) + c3
unsigned get_hash(const char *pat, const char *end) {
  unsigned p = 0;
  for (; pat != end; ++pat)
    p = (p * R + tolower(*pat)) % Q;
  return p;
}

// (c1*r^2 + c2*r + c3 - c1*r^2) * r + c4
unsigned update_hash(unsigned hash, unsigned n, char cf, char cl) {
  unsigned nf = (cf * n) % Q;
  if (hash < nf)
    hash += Q;
  hash = ((hash - nf) * R + cl) % Q;
  return hash;
}

unsigned long long pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned long long mult, prod;
  if (n == 0 || n == 1 || k == 1)
    return n;
  if (k == 0)
    return 1;
  mult = n;
  prod = 1;
  while (k > 0) {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k = k / 2;
  }
  return prod;
}

char *strstrci(char const *needle, char const *haystack) {
  unsigned n, target, cur;
  unsigned left = 0;
  unsigned len = strlen(needle);
  unsigned right = len;
  unsigned i;
  unsigned flag = 0;
  target = get_hash(needle, needle + right);
  cur = get_hash(haystack, haystack + right);
  n = pow_mod(R, right - 1, Q);

  while(haystack[right] != 0) {
    if (target == cur){
        for(i = 0; i < len; ++i){
            if (tolower(needle[i]) != tolower(haystack[left+i])){
                break;
            }
        }
        if (i == len){
            flag = 1;
            break;
        }
    }
    cur = update_hash(cur, n, tolower(haystack[left]), tolower(haystack[right]));
    left += 1;
    right += 1;
  }
  
  return (flag==1) ? (char*)(&haystack[0]) + left : NULL;
}