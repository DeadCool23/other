pub fn read_num<T: std::str::FromStr>() -> Option<T> {
    let mut tmp = String::new();
    return match std::io::stdin().read_line(&mut tmp) {
        Ok(_) => {
            match tmp.trim().parse::<T>() {
                Ok(readed) => { Some(readed) }
                Err(_) => { None }
            }
        }
        Err(_) => { None }
    };
}