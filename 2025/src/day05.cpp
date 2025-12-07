#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "input_reader.h"

struct Range {
    long long start;
    long long end;
};

bool is_fresh(long long id, const std::vector<Range>& ranges) {
    for (const auto& range: ranges) {
        if (id >= range.start && id <= range.end) { return true; }
    }

    return false;
}

bool compare_start_values(const Range& a, const Range& b) {
    return a.start < b.start;
}

void part1(const std::vector<std::string>& lines) {
    std::vector<Range> fresh_ranges;
    long long total_fresh_count = 0;
    bool parsing_ranges = true;

    for (const std::string& line : lines) {
        if (line.empty()) {
            parsing_ranges = false;
            continue;
        }

        if (parsing_ranges) {
            if (line.find('-') != std::string::npos) {
                Range r;
                char dash;
                std::stringstream ss(line);
                ss >> r.start >> dash >> r.end;
                fresh_ranges.push_back(r);
            } else {
                parsing_ranges = false;

                long long id = std::stoll(line);
                if (is_fresh(id, fresh_ranges)) { total_fresh_count++; }
            }
        } else {
            long long id = std::stoll(line);
            if (is_fresh(id, fresh_ranges)) { total_fresh_count++; }
        }
    }

    std::cout << "The total fresh count is " << total_fresh_count << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    std::vector<Range> ranges;

    // parse ranges
    for (const std::string& line : lines) {
        if (line.empty() || line.find('-') == std::string::npos) { break; }

        Range r;
        char dash;
        std::stringstream ss(line);
        ss >> r.start >> dash >> r.end;
        ranges.push_back(r);
    }

    std::sort(ranges.begin(), ranges.end(), compare_start_values);

    long long total_fresh_count = 0;
    long long current_start = ranges[0].start;
    long long current_end = ranges[0].end;
    
    for (size_t i = 1; i < ranges.size(); ++i) {
        if (ranges[i].start > current_end) {
            total_fresh_count += (current_end - current_start + 1);

            current_start = ranges[i].start;
            current_end = ranges[i].end;
        } else {
            current_end = std::max(current_end, ranges[i].end);
        }
    }

    total_fresh_count += (current_end - current_start + 1);

    std::cout << "The total fresh count is " << total_fresh_count << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day05.txt");

    part1(lines);
    part2(lines);

    return 0;
}
