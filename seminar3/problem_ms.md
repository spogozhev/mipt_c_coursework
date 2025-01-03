# Problem MS — слияние для сортировки слиянием

Основная часть алгоритма сортировки слиянием выглядит следующим образом
```
void merge(int *arr, int l, int m, int r);
void merge_sort_imp(int *arr, int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  merge_sort_imp(arr, l, m);
  merge_sort_imp(arr, m + 1, r);
  merge(arr, l, m, r);
}

void merge_sort(int *arr, int n) {
  merge_sort_imp(arr, 0, n - 1);
}
```
Использованная здесь процедура merge сливает сортированный подмассив `arr[l..m]` и сортированный подмассив `arr[m+1..r]`

Ваша задача написать эту функцию с заранее заданной сигнатурой
```
void merge(int *arr, int l, int m, int r) {
  // TODO: ваш код здесь
}
```
Здесь arr это указатель на начало массива, l это начало первого сортированного подмассива, r это конец второго сортированного подмассива, m это точка их разбиения при исходном спуске

Посылка должна состоять из функции merge, описанной выше (допустимо также любое количество вспомогательных), и не должна содержать функции main

## Тесты
<https://github.com/tilir/c-graduate/tree/master/coursework/contests/hwmemory/tests/problem_ms>