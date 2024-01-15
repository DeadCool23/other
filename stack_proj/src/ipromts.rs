#[macro_export]
macro_rules! printf {
    ( $($args:tt)* ) => {
        use std::io::{Write, stdout};
        print!($($args)*);
        stdout().flush().unwrap();
    };
}
pub fn main_menu() {
    println!("+------------------------------+");
    println!("|             Stack            |");
    println!("+------------------------------+");
    println!("| 1: Check is num polinom      |");
    println!("| 2: Check brackets valide     |");
    println!("+------------------------------+");
    println!("| -1: Exit                     |");
    println!("+------------------------------+");
    printf!(": ");
}
