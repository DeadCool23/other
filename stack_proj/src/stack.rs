pub struct Stack<T> {
    element: Option<T>,
    prev: Option<Box<Stack<T>>>,
}

pub mod methods;
