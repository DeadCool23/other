use std::fmt::{Debug, Display, Formatter};

#[derive(Clone, Copy)]
pub struct Point {
    pub x: i32,
    pub y: i32
}
impl Point {
    pub fn new() -> Self {
        Point {
            x: 0,
            y: 0
        }
    }

    pub fn form(x: i32, y: i32) -> Self {
        Point { x, y }
    }
}

impl Display for Point {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl Debug for Point {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "(x: {}, y: {})", self.x, self.y)
    }
}