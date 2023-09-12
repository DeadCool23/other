use scanf::scanf;

pub fn input_person() -> Option<char> {
    print!("Enter Hero to begin: ");
    let mut x: char = '@';
    match scanf!("{}", x) {
        Ok(_) => {},
        Err(_) => {
            println!("ERROR: Incorrect input");
            return None;
        }
    }
    Some(x)
}