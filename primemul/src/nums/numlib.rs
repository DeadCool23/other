/// # Проверка числа на простоту
/// @param [in] number - число
/// @return true - простое, false - иначе
pub fn is_prime(number: i32) -> bool {
    if number <= 1 || (number > 3 && (number % 2 == 0 || number % 3 == 0)) {
        return false;
    }
    if number <= 3 {
        return true;
    }
    for i in (5..=((number as f64).sqrt() as i32)).step_by(6) {
        if number % i == 0 || number % (i + 2) == 0 {
            return false;
        }
    }
    true
}

/// # Перевод числа из строки в число
/// @param [in] snum - число в виде строки
/// @return Опционал с числом
pub fn strtoi<T>(snum: &String) -> Option<T>
where T: std::str::FromStr,
{
    match snum.parse::<T>() {
        Ok(n) => Some(n),
        Err(_) => None,
    }
}
