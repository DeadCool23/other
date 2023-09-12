mod input;
mod race;

fn main() {

    let x = match input::input_person() {
        Some(hero) => hero,
        None => return,
    };

    race::race(x);
}
