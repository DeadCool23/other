use std::{fs::File, io::Read};

const BYTES_PER_LINE: usize = 16;

fn print_address(address: usize) { print!{"{:08X} ", address}; }

fn print_bytes_hex(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    for byte in bytes.iter().take(bytes_cnt) {
        print!("{:02X} ", byte);
    }

    for _ in 0..(BYTES_PER_LINE - bytes_cnt) {
        print!("   ");
    }
}

fn print_bytes_dec(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    for byte in bytes.iter().take(bytes_cnt) {
        let symb = *byte as char;
        if symb.is_ascii_graphic() {
            print!("{}", symb);
        } else {
            print!(".");
        }
    }
}

fn print_bytes(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    print_bytes_hex(bytes, bytes_cnt);
    print!("   ");
    print_bytes_dec(bytes, bytes_cnt);
    println!();
}

pub fn hex_viewer(file: &mut File) -> Result<(), ()> {
    let mut bytes = [0; BYTES_PER_LINE];

    // Читаем данные из файла в буфер и выводим их в шестнадцатеричном виде
    let mut address = 0;
    loop {
        let bytes_read_cnt = match file.read(&mut bytes) {
            Ok(cnt) => cnt,
            Err(_) => { return Err(()); }
        };
        if bytes_read_cnt == 0 { break; }

        print_address(address);
        address += bytes_read_cnt;
        print_bytes(&bytes, bytes_read_cnt);
    }
    Ok(())
}