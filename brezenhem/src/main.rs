mod field;

use std::io;
use field::{
    Field,
    point::Point
};
use crossterm::{
    cursor,
    execute,
    event::{
        Event,
        KeyCode,
        KeyEvent,
        KeyModifiers
    },
    terminal::{
        self,
        disable_raw_mode,
        enable_raw_mode
    }
};
use ansi_term::Colour;
use crate::field::{Boards, Title};

fn main() -> io::Result<()> {
    enable_raw_mode()?;

    let mut field = Field::new();

    let extr_point = Point {
        x: field.width() as i32 - 1,
        y: field.height() as i32 - 1
    };
    let mut dyn_point = extr_point;

    loop {
        terminal_clear()?;
        field.clear();
        field.draw_line(
            Point{x: 0, y:0},
            dyn_point,
        );
        field.print(Boards::All, Title::Name(String::from("Brezenhem")));
        print_point_cords(dyn_point);

        match crossterm::event::read()? {
            Event::Key(KeyEvent {
                           code: KeyCode::Char('q'),
                           modifiers: KeyModifiers::NONE,
                       }) => break,
            Event::Key(KeyEvent {
                           code: KeyCode::Char('w'),
                           modifiers: KeyModifiers::NONE,
                       }) => turn_up(&mut dyn_point),
            Event::Key(KeyEvent {
                           code: KeyCode::Char('a'),
                           modifiers: KeyModifiers::NONE,
                       }) => turn_left(&mut dyn_point),
            Event::Key(KeyEvent {
                           code: KeyCode::Char('s'),
                           modifiers: KeyModifiers::NONE,
                       }) => turn_down(&mut dyn_point),
            Event::Key(KeyEvent {
                           code: KeyCode::Char('d'),
                           modifiers: KeyModifiers::NONE,
                       }) => turn_right(&mut dyn_point),
            Event::Key(KeyEvent {
                           code: KeyCode::Char('r'),
                           modifiers: KeyModifiers::NONE,
                       }) => reset(&mut dyn_point, extr_point),
            _ => {}
        }
    }

    disable_raw_mode()?;
    Ok(())
}

// Очистка терминала
fn terminal_clear() -> io::Result<()> {
    execute!(io::stdout(), terminal::Clear(terminal::ClearType::All))?;
    execute!(io::stdout(), cursor::MoveTo(0, 0))?;
    Ok(())
}

fn turn_left(move_point: &mut Point) {
    move_point.x -= match move_point.x {
        0 => 0,
        _ => 1
    };
}
fn turn_right(move_point: &mut Point) {
    move_point.x += 1;
}

fn turn_up(move_point: &mut Point) {
    move_point.y -= match move_point.y {
        0 => 0,
        _ => 1
    };
}
fn turn_down(move_point: &mut Point) {
    move_point.y += 1;
}

fn reset(move_point: &mut Point, extr_point: Point) {
    move_point.x = extr_point.x;
    move_point.y = extr_point.y;
}

fn print_point_cords(point: Point) {
    let point_cords = format!("| Point: {point:?} |");
    println!("{}", Colour::Yellow.paint(&point_cords));
    print!("{}", Colour::Yellow.paint("+"));
    for _ in 1..(point_cords.len() - 1) {
        print!("{}", Colour::Yellow.paint("-"));
    }
    println!("{}", Colour::Yellow.paint("+"));
}