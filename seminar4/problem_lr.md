# Problem LR — разворот списка

Заранее задан (определять его не надо) тип структуры для односвязного списка
```
struct node_t {
  struct node_t *next;
  int data;
};
```
Следующий код рекурсивно переворачивает список в памяти (вы можете быть уверены, что в списке нет петли)
```
struct node_t * reverse(struct node_t *top) {
  struct node_t *xs;
  if (NULL == top) return NULL;
  if (NULL == top->next) return top;
  xs = reverse(top->next);
  top->next->next = top;
  top->next = NULL;
  return xs;
}
```
Вам необходимо написать и отправить на проверку такую же по смыслу функцию reverse, но работающую итеративно

В посылке должна быть только указанная функция, отправлять функцию main не нужно

### Пример

Входной список: 2 → 4 → 6 → 1

Выходной список: 1 → 6 → 4 → 2

## Тесты
<https://github.com/tilir/c-graduate/tree/master/coursework/contests/hwalg/tests/problem_lr>