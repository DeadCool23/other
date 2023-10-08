pub mod methods;
pub mod operations;

pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<Vec<T>>,
}
