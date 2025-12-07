#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "input_reader.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void part1(const std::vector<std::string>& lines) {
    long long grand_total = 0;
    size_t max_width = 0;
    int start_col = 0;

    for (const auto& line : lines) {
        max_width = std::max(max_width, line.length());
    }

    for (size_t col = 0; col <= max_width; ++col) {
        bool is_seperator = true;

        if (col < max_width) {
            for (const auto& line : lines) {
                char c = (col < line.length()) ? line[col] : ' ';

                if (c != ' ') {
                    is_seperator = false;
                    break;
                }
            }
        }

        if (is_seperator) {
            if (col > start_col) {
                std::vector<long long> numbers;
                char op = ' ';
                const std::string& op_line = lines.back();

                for (size_t k = start_col; k < col; ++k) {
                    if (k < op_line.length() && op_line[k] != ' ') {
                        op = op_line[k];
                        break;
                    }
                }

                for (size_t r = 0; r < lines.size() - 1; ++r) {
                    const std::string& line = lines[r];

                    if (start_col < line.length()) {
                        size_t len = std::min(col - start_col, line.length() - start_col);
                        std::string segment = line.substr(start_col, len);
                        std::string val_str = trim(segment);

                        if (!val_str.empty()) {
                            try {
                                numbers.push_back(std::stoll(val_str));
                            } catch (...) { }
                        }
                    }
                }

                if (!numbers.empty()) {
                    long long current_result = numbers[0];

                    for (size_t i = 1; i < numbers.size(); ++i) {
                        if (op == '+') {
                            current_result += numbers[i];
                        } else if (op == '*') {
                            current_result *= numbers[i];
                        }
                    }

                    grand_total += current_result;
                }
            }

            start_col = col + 1;
        }
    }

    std::cout << "The grand total is " << grand_total << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    long long grand_total = 0;
    size_t max_width = 0;

    for (const auto& line : lines) {
        max_width = std::max(max_width, line.length());
    }

    size_t height = lines.size();
    size_t op_row_idx = height - 1;
    int start_col = 0;

    for (size_t col = 0; col <= max_width; ++col) {
        bool is_separator = true;

        if (col < max_width) {
            for (const auto& line : lines) {
                char c = (col < line.length()) ? line[col] : ' ';
                if (c != ' ') {
                    is_separator = false;
                    break;
                }
            }
        }

        if (is_separator) {
            if (col > start_col) {
                std::vector<long long> numbers;
                char op = ' ';
                const std::string& op_line = lines[op_row_idx];

                for (size_t k = start_col; k < col; ++k) {
                    char c = (k < op_line.length()) ? op_line[k] : ' ';

                    if (c == '+' || c == '*') {
                        op = c;
                        break;
                    }
                }

                for (int c = (int)col - 1; c >= start_col; --c) {
                    std::string num_str = "";

                    for (size_t r = 0; r < op_row_idx; ++r) {
                        const std::string& line = lines[r];
                        char ch = ((size_t)c < line.length()) ? line[c] : ' ';
                        
                        if (isdigit(ch)) {
                            num_str += ch;
                        }
                    }

                    if (!num_str.empty()) {
                        try {
                            numbers.push_back(std::stoll(num_str));
                        } catch (...) {}
                    }
                }

                if (!numbers.empty()) {
                    long long current_result = numbers[0];
                    for (size_t i = 1; i < numbers.size(); ++i) {
                        if (op == '+') current_result += numbers[i];
                        else if (op == '*') current_result *= numbers[i];
                    }
                    grand_total += current_result;
                }
            }
            start_col = col + 1;
        }
    }

    std::cout << "The grand total for part 2 is " << grand_total << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day06.txt");

    part1(lines);
    part2(lines);

    return 0;
}
