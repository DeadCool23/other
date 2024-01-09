use super::super::matrix::Matrix;
use std::{
    fmt::Debug,
    ops::{Add, Mul},
};

impl<T> Add for Matrix<T>
where
    T: std::ops::Add<Output = T>
        + std::ops::Mul<Output = T>
        + std::convert::From<i32>
        + Default
        + Debug
        + Clone
        + Copy,
{
    type Output = Option<Matrix<T>>;

    fn add(self, other: Matrix<T>) -> Option<Matrix<T>> {
        if self.rows == other.rows && self.cols == other.cols {
            let mut result_data = vec![vec![Default::default(); self.cols]; self.rows];
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
}

impl<T> Mul for Matrix<T>
where
    T: std::ops::Add<Output = T>
        + std::ops::Mul<Output = T>
        + std::convert::From<i32>
        + Default
        + Debug
        + Clone
        + Copy,
{
    type Output = Option<Matrix<T>>;

    fn mul(self, other: Matrix<T>) -> Option<Matrix<T>> {
        if self.cols == other.rows {
            let mut result_data = vec![vec![Default::default(); other.cols]; self.rows];
            for i in 0..self.rows {
                for j in 0..other.cols {
                    let mut sum = Default::default();
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
}
