use rand::Rng;
use std::{time::Duration, thread::sleep};

const SIZE: usize = 60;

fn print_race_track(x: char, position: usize, size: usize) {
    print!("|START|");
    for i in 0..size {
        if i == position {
            print!("{}", x);
        } else {
            print!(" ");
        }
    }
    println!("|FINISH|");
}

pub fn race(x: char) {
    let mut position = SIZE / 2;

    loop {
        print_race_track(x, position, SIZE);

        let move_by: i32 = rand::thread_rng().gen_range(-2..=2);
        position = (position as i32 + move_by) as usize;

        if position < 1 {
            println!("You could not finish the race!");
            return;
        }
        if position > SIZE - 1 {
            println!("Yay! You finished the race!");
            return;
        }

        sleep(Duration::from_millis(50));
    }
}
