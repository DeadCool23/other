# Класс матрицы

Класс матрицы, написанный на **Rust**.

## Конструкторы

- `new` - создание экземпляра матрицы
- `empty` - создание нулевой матрицы заданных размеров
- `identity` - создание единичной матрицы
- `from` - создание матрицы

## Методы

### Получение элемента матрицы

- `get_el` - получение элемента матрицы по индексам
- `get_sizes` - получение размеров матрицы
- `get_row` - получение строки по индексу
- `get_col` - получение столбца по индексу

### Добавление элементов

- `add_el` - добавление элемента
- `append_row` - добавление строки в конец
- `append_col` - добавление столбца в конец
- `insert_row` - вставка строки по индексу
- `insert_col` - вставка столбца по индексу

### Удаление элементов

- `del_el` - удаление элемента
- `pop_row` - извлечение строки
- `pop_col` - извлечение столбца
- `remove_row` - удаление строки по индексу
- `remove_col` - удаление столбца по индексу

### Математические операции

- `sum` - сложение матриц
- `multiply` - умножение матриц
- `scalar_sum` - сложение скаляра
- `scalar_multiply` - умножение на скаляр
- `determinant` - вычисление определителя матрицы

### Вывод

- `print` - вывод матрицы
