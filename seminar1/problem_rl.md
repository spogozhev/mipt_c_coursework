#Problem RL -- рекурсия в цикл

Ниже приведён исходный код программы для рекурсивного алгоритма Евклида.

Ваша задача: переписать его так, чтобы вместо рекурсии использовался цикл

Посылка должна состоять из программы, считывающей со стандартного ввода два числа x и y и выводящей на стандартный вывод одно число g.

## Пример 1
Ввод: `2 1`

Вывод: `1`

##Пример 2
Ввод: `3 2`

Вывод: `1`

##Пример 3
Ввод: `2 4`

Вывод: `2`

#Примечания
```
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long x, 
                       unsigned long long y) {
  unsigned long long q;
  if (y > x)
    return gcd(y, x);
  assert (y > 0);
  q = x % y;
  if (q == 0)
    return y;
  return gcd(y, q);
}

int main() {
  unsigned long long x = 0, y = 0, g;
  int res;
  
  res = scanf("%llu %llu", &x, &y);
  assert(res == 2);
  g = gcd(x, y);
  printf("%llu\n", g);
  return 0;
}
```
