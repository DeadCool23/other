pub mod numlib;
pub mod methods;

/// # Структура числа
pub struct Num {
    pub num: Option<i32>,       // Число (В опционале)
    pub as_prime_mul: String    // Представление числа в виде произведения простых чисел
}
