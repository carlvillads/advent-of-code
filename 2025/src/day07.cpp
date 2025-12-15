#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include "input_reader.h"

void part1(const std::vector<std::string>& lines) {
    long long answer = 0;
    int rows = lines.size();
    int cols = lines[0].size();

    std::set<std::pair<int, int>> active_beams;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (lines[r][c] == 'S') {
                active_beams.insert({r, c});
            }
        }
    }

    while (!active_beams.empty()) {
        std::set<std::pair<int, int>> next_beams;

        for (const auto& pos : active_beams) {
            int r = pos.first;
            int c = pos.second;

            int next_r = r + 1;
            int next_c = c;

            if (next_r >= rows) { continue; }

            char cell = lines[next_r][next_c];

            if (cell == '^') {
                answer++;

                if (next_c - 1 >= 0) { next_beams.insert({next_r, next_c - 1}); }
                if (next_c + 1 < cols) { next_beams.insert({next_r, next_c + 1}); }
            } else {
                next_beams.insert({next_r, next_c});
            }
        }

        active_beams = next_beams;
    }

    std::cout << "Split count: " << answer << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    int rows = lines.size();
    int cols = lines[0].size();

    std::map<int, unsigned long long> current_counts;
    int start_r = -1;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (lines[r][c] == 'S') {
                current_counts[c] = 1;
                start_r = r;
            }
        }
    }

    for (int r = start_r; r < rows - 1; ++r) {
        std::map<int, unsigned long long> next_counts;

        for (auto const& [col, count] : current_counts) {
            int next_r = r + 1;
            char target_call = lines[next_r][col];

            if (target_call == '^') {
                if (col - 1 >= 0) { next_counts[col - 1] += count; }
                if (col + 1 < cols) { next_counts[col + 1] += count; }
            } else {
                next_counts[col] += count;
            }
        }

        current_counts = next_counts;
    }

    unsigned long long total_timelines = 0;

    for (auto const& [col, count] : current_counts) {
        total_timelines += count;
    }

    std::cout << "Total timelines: " << total_timelines << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day07.txt");

    part1(lines);
    part2(lines);

    return 0;
}
