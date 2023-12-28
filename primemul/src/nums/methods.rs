use crate::nums::Num;
use super::numlib as nl;
use std::{ops::{Add, Mul}, fmt::{self, Debug}};

/// # Клонирование структуры
impl Clone for Num {
    fn clone(&self) -> Self {
        Num {
            num: self.num,
            as_prime_mul: self.as_prime_mul.clone()
        }
    }
}

/// # Дебажный вывод структур
impl Debug for Num {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Num {{\n\
                         \tnum: {:?} \n\
                         \tas_prime_mul: {:?}\n\
                   }}",
               self.num,
               self.as_prime_mul)
    }
}

/// # Сумма структур
impl Add for Num {
    type Output = Option<Num>;

    fn add(self, other: Self) -> Self::Output {
        if self.num.is_none() || other.num.is_none() {
            return None;
        }
        let add = Num::from_num(self.num.unwrap() + other.num.unwrap());
        Some(add)
    }
}

/// # Произведение структур
impl Mul for Num {
    type Output = Option<Num>;

    fn mul(self, other: Self) -> Self::Output {
        if self.num.is_none() || other.num.is_none() {
            return None;
        }
        let add = Num::from_num(self.num.unwrap() * other.num.unwrap());
        Some(add)
    }
}

impl Num {
    /// # Создание пустой структуры
    pub fn new() -> Self {
        Num {
            num: None,
            as_prime_mul: String::new()
        }
    }

    /// # Создание структуры по числу
    pub fn from_num(num: i32) -> Self {
        Num {
            num: Some(num),
            as_prime_mul: Num::parse_num_to_prime_mul(num)
        }
    }

    /// # Создание структуры по строке
    pub fn from_str(prime_mul: String) -> Self {
        Num {
            num: Num::prime_mul_to_num(&prime_mul),
            as_prime_mul: prime_mul.clone()
        }
    }

    /// # Перезапись строки в структуре
    pub fn rewrite_str(&mut self, prime_mul: String) {
        self.num = Num::prime_mul_to_num(&prime_mul);
        self.as_prime_mul = prime_mul;
    }

    /// # Получение строки структуры
    pub fn get_str(&self) -> String { self.as_prime_mul.clone() }

    /// # Печать строки структуры
    pub fn print_str(&self) {
        match self.num {
            Some(_) => println!("{}", self.as_prime_mul),
            None => println!("Incorrecrt representation of num")
        }
    }

    /// # Перезапись числа в структуре
    pub fn rewrite_num(&mut self, num: i32) {
        self.num = Some(num);
        self.as_prime_mul = Num::parse_num_to_prime_mul(num);
    }

    /// # Получение числа структуры
    pub fn get_num(&self) -> Option<i32> { self.num }

    /// # Печать числа структуры
    pub fn print_num(&self) {
        if let Some(n) = self.num {
            println!("{n}")
        } else {
            println!("NaN")
        }
    }

    /// # Отладочная печать числа структуры
    pub fn dbprint_num(&self) { println!("{:?}", self.num) }

    /// # Парсинг числа на произведение простых чисел
    fn parse_num_to_prime_mul(num: i32) -> String {
        let is_neg = num.is_negative();
        let mut num = num.abs();
        let mut string = String::new();
        for prime_num in (2..=num).filter(|&x| nl::is_prime(x)) {
            let mut cnt = 0;
            while num % prime_num == 0 {
                num /= prime_num;
                cnt += 1;
            }
            if cnt != 0 { string.push_str(&*format!("{prime_num}^{cnt}*")); }
        }
        match string.pop() {
            Some(c) => { if c != '*' { string.push(c) } }
            None => { string.push_str(&*num.to_string()) }
        }
        if is_neg { string = format!("-({string})"); }
        string
    }

    /// # Преобразование произведения простых чисел в число
    /// Некорректная строка обрабатывается
    fn prime_mul_to_num(prime_mul: &String) -> Option<i32> {
        let is_neg: bool;
        match prime_mul.find("-") {
            Some(pos) => { if pos == 0 { is_neg = true } else { return None } }
            None => is_neg = false
        }

        let mut num: i32 = 1;

        let mut is_num = true;

        let mut brackets_opened: usize = 0;
        let mut is_opened_bracket = false;
        let mut is_closed_bracket = false;

        let mut snum = String::new();
        let mut sdig = String::new();

        for char in prime_mul.chars() {
            if is_closed_bracket {
                return None;
            } else if char.is_ascii_digit() {
                if is_num { snum.push(char) } else { sdig.push(char) }
            } else if char == '^' {
                is_num = !is_num;
            } else if char == '*' {
                is_num = !is_num;
                let prime_num = nl::strtoi::<i32>(&snum).unwrap();
                if nl::is_prime(prime_num) {
                    num *= (prime_num).pow(nl::strtoi::<u32>(&sdig).unwrap());
                } else {
                    return  None;
                }
                snum = String::new();
                sdig = String::new();
            } else if char == '-' {
            } else if char == '(' && brackets_opened == 0 {
                is_opened_bracket = true;
                brackets_opened += 1;
            } else if char == ')' && (is_opened_bracket && brackets_opened == 1) {
                is_closed_bracket = true;
            } else {
                return None;
            }
        }

        if is_neg && !is_closed_bracket {
            return if snum.eq("1") {
                Some(-1)
            } else {
                None
            };
        }

        if sdig.is_empty() {
            if num == 1 {
                if snum.eq("0") { num = 0; }
                else if snum.eq("1") { }
                else { return None; }
            } else if snum.is_empty() {
            } else { return None }
        } else {
            let prime_num = nl::strtoi::<i32>(&snum).unwrap();
            if nl::is_prime(prime_num) {
                num *= (prime_num).pow(nl::strtoi::<u32>(&sdig).unwrap());
            } else {
                return  None;
            }
        }

        num = if is_neg { -num } else { num };
        Some(num)
    }
}
