use crate::stack::Stack;
use std::{fmt::{Debug, Display, Formatter, Result}};

impl<T: Clone + Debug> Clone for Stack<T> {
    fn clone(&self) -> Self {
        Stack {
            element: match self.element.clone() {
                Some(el) => Some(el),
                None => None
            },
            prev: match self.prev.clone() {
                Some(prev) => Some(prev),
                None => None
            }
        }
    }
}

impl <T: Clone + Debug> Debug for Stack<T> {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        let mut cnt: usize = 0;
        let mut cur = self;
        while let Some(ref el) = cur.element {
            if cnt == 0 { write!(f, "Stack\n").expect("{wtf}") }
            write!(f, "{}: {:?}\n", cnt + 1, el).expect("{can't be}");
            cnt += 1;
            cur = match &cur.prev {
                None => break,
                Some(prev) => prev,
            };
        }
        if cnt == 0 { write!(f, "Stack is empty").expect("{wtf}") }
        write!(f, "\n")
    }
}

impl <T: Clone + Debug> Display for Stack<T> {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        let mut cur = self;
        while let Some(ref el) = cur.element {
            write!(f, "{:?}\n", el).expect("{can't be}");
            cur = match &cur.prev {
                None => break,
                Some(prev) => prev,
            };
        }
        write!(f, "\n")
    }
}

impl <T: Clone + Debug> Stack<T> {
    pub fn new() -> Self {
        Stack {
            element: None,
            prev: None
        }
    }

    #[warn(dead_code)]
    pub fn form(element: T) -> Self {
        Stack {
            element: Some(element),
            prev: None
        }
    }

    pub fn form_arr(arr: &[T]) -> Self {
        let mut stack = Stack::<T>::new();
        for i in arr.iter() { stack.push(i.clone()); }
        stack
    }

    pub fn push(&mut self, el: T) {
        let new_stack = Stack {
            element: Some(el),
            prev: match self.element {
                None => None,
                Some(_) => Some(Box::new(self.clone()))
            },
        };
        *self = new_stack;
    }

    #[warn(dead_code)]
    pub fn pick(&self) -> Option<T> { self.element.clone() }

    pub fn pop(&mut self) -> Option<T> {
        let element = self.element.take();
        if let Some(prev) = self.prev.take() {
            *self = *prev;
        } else if element.is_some() {
            *self = Stack::new();
        }
        element
    }

    pub fn is_empty(&self) -> bool { self.element.is_none() }

    #[warn(dead_code)]
    pub fn len(&self) -> usize {
        let mut len: usize = 0;
        let mut cur = self;
        while let Some(_) = cur.element {
            len += 1;
            cur = match cur.prev.as_ref() {
                None => break,
                Some(prev) => prev,
            };
        }
        len
    }

    #[warn(dead_code)]
    pub fn each<E: Clone>(&mut self, func: fn(el: T, param: Option<E>) -> T, param: Option<E>) {
        let mut cur = self;
        while let Some(el) = cur.element.as_mut() {
            *el = func(el.clone(), param.clone());
            cur = match cur.prev.as_mut() {
                None => break,
                Some(prev) => prev,
            };
        }
    }
}