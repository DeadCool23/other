mod hexer;
use hexer::hex_viewer;
use std::{env, fs::File, io};

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Usage: hex-viewer <filename>");
        return Ok(());
    }

    let filename = &args[1];
    let mut file = match File::open(filename) {
        Ok(_file)  => _file,
        Err(_) => {
            println!("ERROR: Incorrect file");
            return Ok(());
        }
    };

    match hex_viewer(&mut file) {
        Ok(_) => {},
        Err(_) => println!("ERROR: Incorrect file data")
    };

    Ok(())
}
