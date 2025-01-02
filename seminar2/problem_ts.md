# Problem TS - площадь треугольника

Вам заранее задан тип данных треугольника.

```
struct point_t {
  int x, y;
};
struct triangle_t {
  struct point_t pts[3];
}
```

Ваша задача написать функцию с заданным наперёд именем double_area, которая возвращает его удвоенную площадь.

```
int double_area(struct triangle_t tr);
```

## Пример 1
| Ввод          | Вывод |
| ------------- |------ |
| 1 1 2 2 3 3   | 0     |

## Пример 2
| Ввод            | Вывод |
| --------------- |------ |
| -1 -1 2 -3 3 -2 | 5     |

## Пример 3
| Ввод           | Вывод |
| ---------------|------ |
| 3 -7 5 -2 -4 8 | 65    |

## Тесты
<https://github.com/tilir/c-graduate/tree/master/coursework/contests/hwprimes/tests/problem_ts>