#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include "input_reader.h"

struct Point {
    int r, c;
    bool operator<(const Point& other) const {
        if (r != other.r) { return r < other.r; }
        return c < other.c;
    }
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

struct Shape {
    std::vector<Point> cells;
    int height;
    int width;

    void normalize() {
        if (cells.empty()) { return; }

        int min_r = 1e9, min_c = 1e9;

        for (auto& p : cells) {
            if (p.r < min_r) min_r = p.r;
            if (p.c < min_c) min_c = p.c;
        }

        int max_r = 0, max_c = 0;

        for (auto& p : cells) {
            p.r -= min_r;
            p.c -= min_c;
            if (p.r > max_r) max_r = p.r;
            if (p.c > max_c) max_c = p.c;
        }

        height = max_r + 1;
        width = max_c + 1;
        std::sort(cells.begin(), cells.end());
    }
};

std::vector<Shape> base_shapes;
std::vector<std::vector<Shape>> shape_variations;

Shape rotate(const Shape& s) {
    Shape new_s;
    for (auto& p : s.cells) {
        new_s.cells.push_back({p.c, -p.r});  // (r, c) -> (c, -r)
    }

    new_s.normalize();
    return new_s;
}

Shape flip(const Shape& s) {
    Shape new_s;
    for (auto& p : s.cells) {
        new_s.cells.push_back({p.r, -p.c});  // (r, c) -> (r, -c)
    }

    new_s.normalize();
    return new_s;
}

void precompute_variations() {
    shape_variations.clear();
    shape_variations.resize(base_shapes.size());

    for (size_t i = 0; i < base_shapes.size(); ++i) {
        if (base_shapes[i].cells.empty()) { continue; }

        std::set<std::vector<Point>> unique_set;
        Shape current = base_shapes[i];

        for (int f = 0; f < 2; ++f) {
            for (int r = 0; r < 4; ++r) {
                if (unique_set.find(current.cells) == unique_set.end()) {
                    unique_set.insert(current.cells);
                    shape_variations[i].push_back(current);
                }

                current = rotate(current);
            }

            current = flip(current);
        }
    }
}

bool solve(int idx, const std::vector<int>& pieces_to_place, std::vector<std::vector<bool>>& grid, int W, int H, int last_r, int last_c) {
    if (idx == pieces_to_place.size()) { return true; }

    int shape_id = pieces_to_place[idx];
    const auto& variations = shape_variations[shape_id];

    // Ensure ordering if current piece is same as previous
    bool same_as_prev = (idx > 0 && pieces_to_place[idx] == pieces_to_place[idx-1]);
    int start_r = same_as_prev ? last_r : 0;

    // try all cells
    for (int r = start_r; r < H; ++r) {
        int start_c = (same_as_prev && r == start_r) ? last_c : 0;

        for (int c = start_c; c < W; ++c) {
            for (const auto& var : variations) {  // try every orientation
                if (r + var.height > H || c + var.width > W) { continue; }

                bool fits = true;
                for (const auto& p : var.cells) {
                    if (grid[r + p.r][c + p.c]) {
                        fits = false;
                        break;
                    }
                }

                if (fits) {
                    for (const auto& p : var.cells) { grid[r + p.r][c + p.c] = true; }
                    if (solve(idx+1, pieces_to_place, grid, W, H, r, c)) { return true; }
                    for (const auto& p : var.cells) { grid[r + p.r][c + p.c] = false; }  // backtrack
                }
            }
        }
    }

    return false;
}

void part1(const std::vector<std::string>& lines) {
    base_shapes.clear();
    std::vector<std::string> region_lines;
    int r_counter = 0;
    int current_shape_idx = -1;
    Shape temp_shape;
    
    for(const auto& line : lines) {
        if (line.empty()) {
            if(current_shape_idx != -1 && !temp_shape.cells.empty()) {
                temp_shape.normalize();
                if (base_shapes.size() <= current_shape_idx) base_shapes.resize(current_shape_idx + 1);
                base_shapes[current_shape_idx] = temp_shape;
                temp_shape = Shape();
                current_shape_idx = -1;
            }
            continue;
        }
        
        // Store region lines for later
        if (line.find("x") != std::string::npos && line.find(":") != std::string::npos) {
            region_lines.push_back(line);
            continue;
        }

        // Parse shape header "0:"
        if (isdigit(line[0]) && line.find(':') != std::string::npos) {
            current_shape_idx = std::stoi(line.substr(0, line.find(':')));
            r_counter = 0;
        } else if (current_shape_idx != -1) {
            // Parse shape body
            for(int c=0; c<line.length(); ++c) {
                if(line[c] == '#') {
                    temp_shape.cells.push_back({r_counter, c});
                }
            }
            r_counter++;
        }
    }

    // Capture the final shape if file doesn't end with newline
    if(current_shape_idx != -1 && !temp_shape.cells.empty()) {
        temp_shape.normalize();
        if (base_shapes.size() <= current_shape_idx) base_shapes.resize(current_shape_idx + 1);
        base_shapes[current_shape_idx] = temp_shape;
    }

    precompute_variations();

    int successful_regions = 0;

    for(const auto& line : region_lines) {
        size_t colon = line.find(':');
        size_t x_pos = line.find('x');
        
        int W = std::stoi(line.substr(0, x_pos));
        int H = std::stoi(line.substr(x_pos + 1, colon - (x_pos + 1)));
        
        std::stringstream ss(line.substr(colon + 1));
        std::vector<int> pieces_to_place;
        int count;
        int s_id = 0;
        int total_area = 0;
        
        while(ss >> count) {
            if (s_id < base_shapes.size()) {
                for(int k=0; k<count; ++k) {
                    pieces_to_place.push_back(s_id);
                    total_area += base_shapes[s_id].cells.size();
                }
            }
            s_id++;
        }

        if (total_area > W * H) { continue; }

        std::sort(pieces_to_place.begin(), pieces_to_place.end(), [](int a, int b){
            return base_shapes[a].cells.size() > base_shapes[b].cells.size();  // Sort largest pieces first
        });

        std::vector<std::vector<bool>> grid(H, std::vector<bool>(W, false));
        
        if (solve(0, pieces_to_place, grid, W, H, 0, 0)) {
            successful_regions++;
        }
    }

    std::cout << "Part 1: " << successful_regions << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    std::cout << "Happy Holidays!" << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day12.txt");

    part1(lines);
    part2(lines);

    return 0;
}
