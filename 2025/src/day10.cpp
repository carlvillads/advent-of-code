#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>
#include <cmath>
#include <iomanip>
#include "input_reader.h"

struct Machine {
    int num_lights;
    std::vector<int> target_state;
    std::vector<int> joltage_target;
    std::vector<std::vector<int>> buttons;
};

Machine parse_machine(const std::string& line) {
    Machine m;

    // parse light diagram
    size_t open_bracket = line.find('[');
    size_t close_bracket = line.find(']');
    std::string pattern = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);

    m.num_lights = pattern.length();
    m.target_state.resize(m.num_lights);

    for (int i = 0; i < m.num_lights; ++i) {
        m.target_state[i] = (pattern[i] == '#') ? 1 : 0;
    }

    // parse buttons
    size_t pos = close_bracket + 1;
    size_t tuborg_pos = line.find('{');

    while ((pos = line.find('(', pos)) != std::string::npos) {
        if (tuborg_pos != std::string::npos && pos > tuborg_pos) { break; }

        size_t end = line.find(')', pos);
        std::string content = line.substr(pos + 1, end - pos - 1);
        std::vector<int> btn(m.num_lights, 0);
        std::stringstream ss(content);
        std::string segment;

        while (std::getline(ss, segment, ',')) {
            if (!segment.empty()) {
                int idx = std::stoi(segment);
                if (idx >= 0 && idx < m.num_lights) {
                    btn[idx] = 1;
                }
            }
        }

        m.buttons.push_back(btn);
        pos = end + 1;
    }

    if (tuborg_pos != std::string::npos) {
        size_t tuborg_end = line.find('}', tuborg_pos);
        std::string content = line.substr(tuborg_pos + 1, tuborg_end - tuborg_pos - 1);
        std::stringstream ss(content);
        std::string segment;

        while (std::getline(ss, segment, ',')) {
            if (!segment.empty()) {
                m.joltage_target.push_back(std::stoi(segment));
            }
        }
    }

    return m;
}

int solve_for_min_presses(const Machine& m) {
    int R = m.num_lights;
    int C = m.buttons.size();

    // M[R * (C+1)]
    std::vector<std::vector<int>> M(R, std::vector<int>(C + 1));
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            M[r][c] = m.buttons[c][r];
        }
        M[r][C] = m.target_state[r];
    }

    // gaussian elemination
    int pivot_row = 0;
    std::vector<int> col_to_pivot_row(C, -1);
    std::vector<bool> is_free_var(C, true);

    for (int c = 0; c < C && pivot_row < R; ++c) {
        // find the pivot
        int sel = -1;
        for (int r = pivot_row; r < R; ++r) {
            if (M[r][c] == 1) {
                sel = r;
                break;
            }
        }

        if (sel == -1) { continue; }  // col is a free variable
        
        std::swap(M[pivot_row], M[sel]);

        for (int r = 0; r < R; ++r) {
            if (r != pivot_row && M[r][c] == 1) {
                for (int k = c; k <= C; ++k) {
                    M[r][k] ^= M[pivot_row][k];  // XOR
                }
            }
        }

        col_to_pivot_row[c] = pivot_row;
        is_free_var[c] = false;
        pivot_row++;
    }

    // minimize hamming weight by brute force
    std::vector<int> free_vars;
    for (int c = 0; c < C; ++c) {
        if (is_free_var[c]) { free_vars.push_back(c); }
    }

    int num_free = free_vars.size();
    int min_presses = INT_MAX;
    long long limit = 1LL << num_free;  // 2^num_free possibilities

    for (long long mask = 0; mask < limit; ++mask) {
        std::vector<int> x(C, 0);
        int current_presses = 0;

        for (int i = 0; i < num_free; ++i) {
            if ((mask >> i) & 1) {
                x[free_vars[i]] = 1;
                current_presses++;
            }
        }

        for (int c = C - 1; c >= 0; --c) {
            if (!is_free_var[c]) {
                int r = col_to_pivot_row[c];
                int val = M[r][C];
                // XOR the sum
                for (int k = c + 1; k < C; ++k) {
                    if (M[r][k]) {
                        val ^= x[k];
                    }
                }

                x[c] = val;
                if (val) { current_presses++; }
            }
        }

        if (current_presses < min_presses) {
            min_presses = current_presses;
        }
    }

    return (min_presses == INT_MAX) ? 0 : min_presses;
}

long long solve_for_min_presses_joltage(const Machine& m) {
    int R = m.joltage_target.size();
    int C = m.buttons.size();
    std::vector<std::vector<double>> M(R, std::vector<double>(C + 1));

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (r < m.buttons[c].size()) {
                M[r][c] = (double)m.buttons[c][r];
            } else {
                M[r][c] = 0.0;
            }
        }
        M[r][C] = (double)m.joltage_target[r];
    }

    // Gaussian Elimination
    int pivot_row = 0;
    std::vector<int> col_to_pivot_row(C, -1);
    std::vector<bool> is_free_var(C, true);
    const double EPS = 1e-9;

    for (int c = 0; c < C && pivot_row < R; ++c) {
        int sel = -1;
        double max_val = EPS;
        for (int r = pivot_row; r < R; ++r) {
            if (std::abs(M[r][c]) > max_val) {
                max_val = std::abs(M[r][c]);
                sel = r;
            }
        }

        if (sel == -1) { continue; }

        std::swap(M[pivot_row], M[sel]);

        double div = M[pivot_row][c];
        for (int k = c; k <= C; ++k) {
            M[pivot_row][k] /= div;
        }

        for (int r = 0; r < R; ++r) {
            if (r != pivot_row) {
                double factor = M[r][c];
                if (std::abs(factor) > EPS) {
                    for (int k = c; k <= C; ++k) {
                        M[r][k] -= factor * M[pivot_row][k];
                    }
                }
            }
        }

        col_to_pivot_row[c] = pivot_row;
        is_free_var[c] = false;
        pivot_row++;
    }

    std::vector<int> free_vars;
    for (int c = 0; c < C; ++c) {
        if (is_free_var[c]) free_vars.push_back(c);
    }

    long long min_presses = -1;
    long long range_limit = 100;
    if (free_vars.empty()) { range_limit = 1; }

    int num_free = free_vars.size();
    auto solve_recursive = [&](auto&& self, int idx, std::vector<long long>& current_x) -> void {
        if (idx == num_free) {
            long long current_total = 0;
            bool possible = true;
            std::vector<long long> full_x(C);

            for(int i=0; i<num_free; ++i) {
                full_x[free_vars[i]] = current_x[i];
                current_total += current_x[i];
            }

            for (int c = C - 1; c >= 0; --c) {
                if (!is_free_var[c]) {
                    int r = col_to_pivot_row[c];
                    double val = M[r][C];
                    for (int k = c + 1; k < C; ++k) {
                        val -= M[r][k] * (double)full_x[k];
                    }
                    
                    // Check if int
                    double nearest = std::round(val);
                    if (std::abs(val - nearest) > 1e-4) {
                        possible = false;
                        break;
                    }

                    long long x_val = (long long)nearest;
                    
                    if (x_val < 0) {
                        possible = false;
                        break;
                    }
                    
                    full_x[c] = x_val;
                    current_total += x_val;
                }
            }

            if (possible) {
                if (min_presses == -1 || current_total < min_presses) {
                    min_presses = current_total;
                }
            }
            return;
        }

        for (int i = 0; i <= 200; ++i) {
             current_x[idx] = i;
             self(self, idx + 1, current_x);
        }
    };

    std::vector<long long> free_vals(num_free);
    solve_recursive(solve_recursive, 0, free_vals);

    return (min_presses == -1) ? 0 : min_presses;
}

void part1(const std::vector<std::string>& lines) {
    long long total_presses = 0;
    
    for (const auto& line : lines) {
        if (line.empty()) { continue; }

        Machine m = parse_machine(line);
        int result = solve_for_min_presses(m);

        total_presses += result;
    }

    std::cout << "Part 1: The number of total presses is: " << total_presses << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    long long total_presses = 0;
    
    for (const auto& line : lines) {
        if (line.empty()) { continue; }

        Machine m = parse_machine(line);
        total_presses += solve_for_min_presses_joltage(m);
    }

    std::cout << "Part 2: The fewest button presses requered: " << total_presses << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day10.txt");

    part1(lines);
    part2(lines);

    return 0;
}
