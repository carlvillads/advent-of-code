fn main() {
    let input = include_str!("../../inputs/day01.txt");

    let p1 = part1(input);
    println!("The answer to part 1 is: {}", p1);

    let p2 = part2(input);
    println!("The answer to part 2 is: {}", p2);
}

fn part1(input: &str) -> String {
    let mut current_pos = 50;
    let mut pos_zero = 0;

    for line in input.lines() {
        let (dir_str, amount_str) = line.split_at(1);
        let direction = dir_str.chars().next().unwrap();
        let amount: i32 = amount_str.parse().unwrap();

        if direction == 'R' {
            current_pos = (current_pos  + amount) % 100;
        } else if direction == 'L' {
            current_pos = ((current_pos - amount) % 100 + 100) % 100;
        }

        if current_pos == 0 {
            pos_zero += 1;
        }
    }

    return pos_zero.to_string();
}

fn part2(input: &str) -> String {
    let mut passed_zero_count = 0;
    let mut current_pos = 50;

    for line in input.lines() {
        let (dir_str, amt_str) = line.split_at(1);
        let direction = dir_str.chars().next().unwrap();
        let amount: i32 = amt_str.parse().unwrap();

        if direction == 'R' {
            // Integer division behaves the same in Rust as C++
            passed_zero_count += (current_pos + amount) / 100;
            current_pos = (current_pos + amount) % 100;
        } else if direction == 'L' {
            let inverse_dist = (100 - current_pos) % 100;
            passed_zero_count += (inverse_dist + amount) / 100;

            current_pos = ((current_pos - amount) % 100 + 100) % 100;
        }
    }

    return  passed_zero_count.to_string();
}
