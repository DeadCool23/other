use std::mem::swap;
use super::point::Point;

fn get_step(num: i32) -> i8 {
    match num {
        0 => 0,
        0.. => 1,
        ..=0 => -1
    }
}

pub fn brezenhem(beg: Point, end: Point) -> Vec<Point> {
    let mut dx = (end.x - beg.x).abs();
    let mut dy = (end.y - beg.y).abs();

    let xstep = get_step(dx);
    let ystep = get_step(dy);

    let exch = if dy > dx {
        swap(&mut dx, &mut dy);
        true
    } else {
        false
    };

    let ddif = dy as f64 / dx as f64;

    let mut er: f64 = ddif - 0.5;

    let mut point = Point::form(beg.x, beg.y);
    let mut points = Vec::<Point>::new();
    for _ in 0..=dx {
        points.push(point);

        if er >= 0. {
           if exch {
               point.x += xstep as i32;
           } else {
               point.y += ystep as i32;
           };

           er -= 1.;
        }

        if exch {
            point.y += ystep as i32;
        } else {
            point.x += xstep as i32;
        };

        er += ddif;
    }

    points
}