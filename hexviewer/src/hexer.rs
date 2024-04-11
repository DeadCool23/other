use lazy_static::lazy_static;
use std::{fs::File, io::Read};
use ansi_term::{Colour, Style};

const BYTES_PER_LINE: usize = 16;

const LINK_SEP: &str = "+";
const HORIZONT_SEP: &str = "-";
const VERTICAL_SEP: &str = "|";

lazy_static! {
    static ref SEP_STYLE: Style = Style::default();
    static ref BYTE_STYLE: Style = Style::from(Colour::RGB(0xFF, 0xFF, 0xFF));
    static ref DECODE_STYLE: Style = Style::from(Colour::RGB(0xFF, 0xFF, 0xFF)).italic();
    static ref ADRESS_STYLE: Style = Style::from(Colour::RGB(0xFF, 0xFF, 0xFF)).italic();
}

fn horizontal_bord() {
    println!(
        "{3}{0}{3}{1}{3}{2}{3}",
        SEP_STYLE.paint(HORIZONT_SEP.repeat(8)),
        SEP_STYLE.paint(HORIZONT_SEP.repeat(BYTES_PER_LINE * 3 + 2 * 1)),
        SEP_STYLE.paint(HORIZONT_SEP.repeat(BYTES_PER_LINE)),
        SEP_STYLE.paint(LINK_SEP)
    );
}

fn print_address(address: usize) {
    print!(
        "{0}{1}{0} ",
        SEP_STYLE.paint(VERTICAL_SEP),
        ADRESS_STYLE.paint(format!("{:08X}", address))
    );
}

fn print_bytes_hex(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    let mut printed = 0;
    for byte in bytes.iter().take(bytes_cnt) {
        print!("{} ", BYTE_STYLE.paint(format!("{:02X}", byte)));
        printed += 1;
        if printed == BYTES_PER_LINE / 2 {
            print!(" ");
        }
    }

    for _ in 0..(BYTES_PER_LINE - bytes_cnt) {
        print!("   ");
    }
}

fn print_bytes_dec(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    for byte in bytes.iter().take(bytes_cnt) {
        let symb = *byte as char;
        if symb.is_ascii_graphic() {
            print!("{}", DECODE_STYLE.paint(symb.to_string()));
        } else {
            print!(".");
        }
    }

    for _ in 0..(BYTES_PER_LINE - bytes_cnt) {
        print!(" ");
    }
}

fn print_bytes(bytes: &[u8; BYTES_PER_LINE], bytes_cnt: usize) {
    print_bytes_hex(bytes, bytes_cnt);
    print!("{}", SEP_STYLE.paint(VERTICAL_SEP));
    print_bytes_dec(bytes, bytes_cnt);
    println!("{}", SEP_STYLE.paint(VERTICAL_SEP));
}

pub fn hex_viewer(file: &mut File) -> Result<(), ()> {
    let mut bytes = [0; BYTES_PER_LINE];

    let mut address = 0;
    horizontal_bord();
    loop {
        let bytes_read_cnt = match file.read(&mut bytes) {
            Ok(cnt) => cnt,
            Err(_) => {
                return Err(());
            }
        };
        if bytes_read_cnt == 0 {
            break;
        }

        print_address(address);
        address += bytes_read_cnt;
        print_bytes(&bytes, bytes_read_cnt);
    }
    horizontal_bord();
    Ok(())
}
