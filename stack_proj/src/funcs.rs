use super::stack::Stack;

pub fn is_polinom(num: u32) -> bool {
    let digs: Vec<u8> = num
        .to_string()
        .chars()
        .map(|c| c.to_digit(10).unwrap() as u8)
        .collect();
    let mut stack = Stack::form_arr(&digs[..(digs.len() / 2)]);
    for digit in &digs[if digs.len() % 2 == 0 { digs.len() / 2 } else { digs.len() / 2 + 1 }..] {
        let rev_dig = match stack.pop() {
            None => return false,
            Some(dig) => dig,
        };
        if *digit != rev_dig { return false }
    }
    true
}


use lazy_static::lazy_static;

const BRACKETS_CNT: usize = 4;

lazy_static! {
    static ref BRACKETS: String = "{[(<}])>".to_string();
    static ref OPENED_BRACKETS: String = BRACKETS.clone()[..BRACKETS_CNT].to_string();
    static ref CLOSED_BRACKETS: String = BRACKETS.clone()[BRACKETS_CNT..].to_string();
}

fn brackets_eq(open: char, close: char) -> bool { OPENED_BRACKETS.find(open) == CLOSED_BRACKETS.find(close) }

pub fn is_valide_brackets(expr: &str) -> bool {
    let mut opened_brackets: Stack<char> = Stack::new();
    for c in expr.chars() {
        if BRACKETS.find(c).is_some() {
            if OPENED_BRACKETS.find(c).is_some() {
                opened_brackets.push(c);
            } else if CLOSED_BRACKETS.find(c).is_some() {
                let last_opened = match opened_brackets.pop() {
                    None => return false,
                    Some(c) => c,
                };
                if !brackets_eq(last_opened, c) { return false; }
            }
        }
    }
    if opened_brackets.is_empty() { true } else { false }
}