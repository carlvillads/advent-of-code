#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "input_reader.h"

void part1(const std::vector<std::string>& lines) {
    int pos_zero = 0;
    int current_pos = 50;

    for (const auto& line : lines) {
        char direction = line[0];
        int amount = std::stoi(line.substr(1));

        if (direction == 'R') {
            current_pos = (current_pos + amount) % 100;
        } else if (direction == 'L') {
            current_pos = ((current_pos - amount) % 100 + 100) % 100;
        }

        if (current_pos == 0) {
            pos_zero += 1;
        }
    }

    std::cout << "The password is " << pos_zero << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    int passed_zero_count = 0;
    int current_pos = 50;

    for (const auto& line : lines) {
        char direction = line[0];
        int amount = std::stoi(line.substr(1));

        if (direction == 'R') {
            passed_zero_count += (current_pos + amount) / 100;

            current_pos = (current_pos + amount) % 100;
        } else if (direction == 'L') {
            int inverse_dist = (100 - current_pos) % 100;
            passed_zero_count += (inverse_dist + amount) / 100;

            current_pos = ((current_pos - amount) % 100 + 100) % 100;
        }
    }
    
    std::cout << "The real password is " << passed_zero_count << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day01.txt");

    part1(lines);
    part2(lines);

    return 0;
}
