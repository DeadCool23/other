mod brezenhem;
pub mod point;


use PartialEq;
use std::cmp::max;
use ansi_term::Colour;
use brezenhem::brezenhem;
use crate::field::point::Point;
use std::fmt::{Debug, Display, Formatter};

const WIDTH: usize = 70;
const HEIGHT: usize = 10;

#[derive(PartialEq, Clone, Copy)]
pub enum Boards {
    All,
    None,
}

pub enum Title {
    None,
    Name(String)
}

pub struct Field {
    width: usize,
    height: usize,
    field: Vec<Vec<char>>
}


impl Field {
    pub fn new() -> Self {
        Field {
            width: WIDTH,
            height: HEIGHT,
            field: vec![vec!['.'; WIDTH]; HEIGHT]
        }
    }

    pub fn form(h: usize, w: usize) -> Self {
        Field {
            width: h,
            height: w,
            field: vec![vec!['.'; w]; h]
        }
    }

    pub fn width(&self) -> usize { self.width }
    pub fn height(&self) -> usize { self.height }

    pub fn draw_line(&mut self, beg: Point, end: Point) {
        let points = brezenhem(beg, end);
        let i_width = WIDTH as i32;
        let i_height = HEIGHT as i32;
        for point in points.iter().as_ref() {
            if (point.x < i_width && point.x >= 0) && (point.y < i_height && point.y >= 0) {
                self.field[point.y as usize][point.x as usize] = 'x';
            }
        }
    }

    pub fn clear(&mut self) {
        self.field = vec![vec!['.'; self.width]; self.height];
    }

    fn print_buttom(length: i32) {
        for i in -1..=length {
            if i == -1 || i == length {
                print!("+");
            } else {
                print!("-");
            }
        }
        print!("\n")
    }

    fn print_up(length: i32, title: String) {
        let length = length + 1 - title.len() as i32;
        for i in -1..=length {
            if i == -1 || i == length {
                print!("+");
            } else if i == 0 && title.len() != 0 {
                print!("{}", Colour::Yellow.bold().paint(&title));
            } else {
                print!("-");
            }
        }
        print!("\n")
    }

    fn print_board(boards: Boards) {
        match boards {
            Boards::All => print!("|"),
            Boards::None => print!("")
        }
    }

    pub fn print(&self, boards: Boards, title: Title) {
        let title = match title {
            Title::None => String::new(),
            Title::Name(str) => str.clone()
        };

        let wboar_len = max(self.width, title.len()) as i32;
        Self::print_up(wboar_len, title);
        for i in 0..(self.height as i32) {
            Self::print_board(boards);
            for j in 0..wboar_len {
                print!("{}", if j < self.width as i32 {
                    self.field[i as usize][j as usize]
                } else {
                    ' '
                });
            }
            Self::print_board(boards);
            print!("\n");
        }
        Self::print_buttom(wboar_len);
    }
}

impl Display for Field {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        for i in -1..=(self.height as i32) {
            for j in -1..=(self.width as i32) {
                let symb = if (i == -1 || i == self.height as i32) && (j == -1 || j == self.width as i32) {
                    '+'
                } else if j == -1 || j == self.width as i32 {
                    '|'
                } else if i == -1 || i == self.height as i32 {
                    '-'
                } else {
                    self.field[i as usize][j as usize]
                };

                match write!(f, "{}", symb) {
                    Err(e) => return Err(e),
                    Ok(_) => {}
                };
            }
            match write!(f, "\n") {
                Err(e) => return Err(e),
                Ok(_) => {}
            };
        }
        Ok(())
    }
}

impl Debug for Field {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        for i in 0..self.height {
            for j in 0..self.width {
                match write!(f, "{}", self.field[i][j]) {
                    Err(e) => return Err(e),
                    Ok(_) => {}
                };
            }
            match write!(f, "\n") {
                Err(e) => return Err(e),
                Ok(_) => {}
            };
        }
        Ok(())
    }
}