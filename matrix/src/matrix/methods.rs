use super::super::matrix::Matrix;
use std::{default::Default, fmt::Display, vec};

impl<T> Matrix<T>
where
    T: std::ops::Add<Output = T>
        + std::ops::Mul<Output = T>
        + std::convert::From<i32>
        + Default
        + Display
        + Clone
        + Copy,
{
    //==========================================================================
    // Конструкторы

    /**
     * # Конструктор нулевой матрицы
     */
    pub fn new() -> Self {
        Matrix {
            rows: 0,
            cols: 0,
            data: vec![vec![]],
        }
    }

    /**
     * # Конструктор нулевой матрицы
     *
     * Матрица заданных размеров
     * заполняется нулевыми значениями
     */
    pub fn empty(rows: usize, cols: usize) -> Self {
        let mut data: Vec<Vec<T>> = Vec::new();
        for i in 0..rows {
            data.push(Vec::new());
            for _ in 0..cols {
                data[i].push(T::default());
            }
        }

        Matrix { rows, cols, data }
    }

    /**
     * # Конструктор матрицы
     *
     * Матрица заданных размеров
     * заполняется заданными значениями
     */
    pub fn form(rows: usize, cols: usize, data: Vec<Vec<T>>) -> Self {
        Matrix { rows, cols, data }
    }

    pub fn identity(size: usize) -> Self {
        let mut data = Vec::with_capacity(size);
        for i in 0..size {
            let mut row = Vec::with_capacity(size);
            for j in 0..size {
                if i == j {
                    row.push(<i32 as Into<T>>::into(1));
                } else {
                    row.push(T::default());
                }
            }
            data.push(row);
        }

        Matrix {
            rows: size,
            cols: size,
            data,
        }
    }

    //==========================================================================
    /// #Получение элемента матрицы по индексам
    pub fn get(&self, row: usize, col: usize) -> Option<T> {
        if row < self.rows && col < self.cols {
            Some(self.data[row][col])
        } else {
            None
        }
    }

    /// # Получение строки по индексу
    pub fn get_row(&mut self, ind: usize) -> Option<Vec<T>> {
        if ind >= self.rows {
            return None;
        }
        Some(self.data[ind].clone())
    }

    /// # Получение столбца по индексу
    pub fn get_col(&mut self, ind: usize) -> Option<Vec<T>> {
        if ind >= self.cols {
            return None;
        }
        let mut col: Vec<T> = vec![];
        for i in 0..self.rows {
            col.push(self.data[i][ind])
        }
        Some(col)
    }

    //==========================================================================
    // Добавление элементов, строки и столбца к матрице
    pub fn add_el(&mut self, row: usize, col: usize, value: T) -> Option<T> {
        if row < self.rows && col < self.cols {
            self.data[row][col] = value;
            Some(value)
        } else {
            None
        }
    }

    pub fn append_row(&mut self, row: Vec<T>) -> bool {
        if self.cols != row.len() {
            return false;
        };

        self.data.push(row);
        self.rows += 1;
        true
    }

    pub fn append_col(&mut self, col: Vec<T>) -> bool {
        if self.rows != col.len() {
            return false;
        };

        for i in 0..self.rows {
            self.data[i].push(col[i]);
        }
        self.cols += 1;
        true
    }

    pub fn insert_col(&mut self, ind: usize, col: Vec<T>) -> bool {
        if self.cols < ind || col.len() != self.rows {
            return false;
        };

        for i in 0..self.rows {
            self.data[i].insert(ind, col[i]);
        }
        self.cols += 1;
        true
    }

    pub fn insert_row(&mut self, ind: usize, row: Vec<T>) -> bool {
        if self.rows < ind || row.len() != self.cols {
            return false;
        };

        self.data.insert(ind, row);
        self.rows += 1;
        true
    }

    //=================================================================
    // Удаление

    /// # Удаление элемента по позиции
    pub fn del_el(&mut self, row: usize, col: usize) -> Option<T> {
        if row < self.rows && col < self.cols {
            let value = self.data[row][col];
            self.data[row][col] = T::default();
            Some(value)
        } else {
            None
        }
    }

    /// # Удаление последней строки
    pub fn pop_row(&mut self) -> Option<Vec<T>> {
        let row = self.data.pop();
        match row {
            Some(_) => self.rows -= 1,
            _ => {}
        }
        row
    }

    /// # Удаление последнего столбца
    pub fn pop_col(&mut self) -> Option<Vec<T>> {
        let mut col: Vec<T> = vec![];
        for i in 0..self.rows {
            match self.data[i].pop() {
                Some(el) => col.push(el),
                None => return None,
            }
        }
        self.cols -= 1;
        Some(col)
    }

    /// # Удаление строки по индексу
    pub fn remove_row(&mut self, ind: usize) -> Option<Vec<T>> {
        if ind >= self.rows {
            return None;
        }
        let row = self.data.remove(ind);
        self.rows -= 1;
        Some(row)
    }

    /// # Удаление столбца по индексу
    pub fn remove_col(&mut self, ind: usize) -> Option<Vec<T>> {
        if ind >= self.cols {
            return None;
        }
        let mut col: Vec<T> = vec![];
        for i in 0..self.rows {
            col.push(self.data[i].remove(ind))
        }
        self.cols -= 1;
        Some(col)
    }

    //=================================================================
    // Math

    /// # Сумма матриц
    pub fn sum(&self, other: &Matrix<T>) -> Option<Matrix<T>> {
        if self.rows == other.rows && self.cols == other.cols {
            let mut result_data = vec![vec![T::default(); self.cols]; self.rows];
            for i in 0..self.rows {
                for j in 0..self.cols {
                    result_data[i][j] = self.data[i][j].clone() + other.data[i][j].clone();
                }
            }
            Some(Matrix::form(self.rows, self.cols, result_data))
        } else {
            None
        }
    }

    /// # Произведение матриц
    pub fn multiply(&self, other: &Matrix<T>) -> Option<Matrix<T>> {
        if self.cols == other.rows {
            let mut result_data = vec![vec![T::default(); other.cols]; self.rows];
            for i in 0..self.rows {
                for j in 0..other.cols {
                    let mut sum = T::default();
                    for k in 0..self.cols {
                        sum = sum + self.data[i][k].clone() * other.data[k][j].clone();
                    }
                    result_data[i][j] = sum;
                }
            }
            Some(Matrix::form(self.rows, other.cols, result_data))
        } else {
            None
        }
    }

    /// # Сложение матрицы с числом
    pub fn scalar_sum(&self, scalar: T) -> Matrix<T> {
        let mut result_data = vec![vec![T::default(); self.cols]; self.rows];
        for i in 0..self.rows {
            for j in 0..self.cols {
                result_data[i][j] = self.data[i][j].clone() + scalar.clone();
            }
        }
        Matrix::form(self.rows, self.cols, result_data)
    }

    /// # Умножение матрицы на число
    pub fn scalar_multiply(&self, scalar: T) -> Matrix<T> {
        let mut result_data = vec![vec![T::default(); self.cols]; self.rows];
        for i in 0..self.rows {
            for j in 0..self.cols {
                result_data[i][j] = self.data[i][j].clone() * scalar.clone();
            }
        }
        Matrix::form(self.rows, self.cols, result_data)
    }

    /// # Поиск определителя матрицы
    pub fn determinant(&self) -> Option<T> {
        if self.rows != self.cols {
            return None;
        }

        let n = self.rows;
        if n == 1 {
            return Some(self.data[0][0]);
        }

        let mut det: T = T::default();

        for col in 0..n {
            let mut submatrix = Vec::new();

            for row in 1..n {
                let mut subrow = Vec::new();

                for j in 0..n {
                    if j != col {
                        subrow.push(self.data[row][j]);
                    }
                }

                submatrix.push(subrow);
            }

            let minor = Matrix::form(n - 1, n - 1, submatrix);
            let sign: T = if col % 2 == 0 {
                <i32 as Into<T>>::into(1)
            } else {
                <i32 as Into<T>>::into(-1)
            };
            det = det + sign * self.data[0][col] * minor.determinant().unwrap_or(T::default());
        }

        Some(det)
    }

    //===================================================
    // Вывод
    pub fn print(&self) {
        if self.rows == 0 || self.cols == 0 {
            println!("Empty matrix");
            return;
        }

        for i in 0..self.rows {
            for j in 0..self.cols {
                print!("{} ", self.data[i][j]);
            }
            println!();
        }
    }
}
