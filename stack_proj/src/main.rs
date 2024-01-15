mod funcs;
mod stack;
mod reader;
mod ipromts;

fn main() {
    ipromts::main_menu();
    let act = match reader::read_num::<i32>() {
        Some(act) => {
            match act {
                1..=2 | -1 => act,
                _ => 0
            }
        }
        None => 0
    };

    if act == 1 {
        printf!("\nInput polinom: ");
        let num = match reader::read_num::<u32>() {
            None => {
                println!("\nERROR: Incorrect input");
                return;
            }
            Some(num) => num
        };
        println!("\n{num} - {}", if funcs::is_polinom(num) {
            "is polinom"
        } else {
            "isn't polinom"
        })
    } else if act == 2 {
        printf!("\nInput expresion: ");
        let mut expr = String::new();
        match std::io::stdin().read_line(&mut expr) {
            Ok(_) => {},
            Err(_) => {
                println!("\nERROR: Incorrect input");
                return;
            }
        }
        let expr = expr.trim();
        println!("\nIn expr \"{expr}\" brackets {}", if funcs::is_valide_brackets(&expr) {
            "valide"
        } else {
            "invalide"
        })
    } else if act == -1 {
        println!("\nExit application...");
    } else {
        println!("\nERROR: Incorrect action");
    }
}