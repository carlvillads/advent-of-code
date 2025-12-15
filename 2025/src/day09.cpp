#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "input_reader.h"

struct Point {
    int x;
    int y;
};

bool is_strictly_between(int v, int a, int b) {
    return (v > std::min(a, b)) && (v < std::max(a, b));
}

bool ranges_overlap(int a1, int a2, int b1, int b2) {
    return std::max(a1, a2) >= std::min(b1, b2) &&
           std::min(a1, a2) <= std::max(b1, b2);
}

bool is_valid_rectangle(const Point& r1, const Point& r2, const std::vector<Point>& poly) {
    int min_x = std::min(r1.x, r2.x);
    int max_x = std::max(r1.x, r2.x);
    int min_y = std::min(r1.y, r2.y);
    int max_y = std::max(r1.y, r2.y);
    size_t n = poly.size();

    for (size_t i = 0; i < n; ++i) {
        Point pA = poly[i];
        Point pB = poly[(i + 1) % n];

        if (pA.x == pB.x) {
            if (is_strictly_between(pA.x,  min_x, max_x)) {
                if (ranges_overlap(pA.y, pB.y, min_y, max_y)) { return false; }
            }
        } else if (pA.y == pA.y) {
            if (is_strictly_between(pA.y, min_y, max_y)) {
                if (ranges_overlap(pA.x, pB.x, min_x, max_x)) { return false; }
            }
        }
    }

    double mid_x = (min_x + max_x) / 2.0;
    double mid_y = (min_y + max_y) / 2.0;
    int intersections = 0;

    for (size_t i = 0; i < n; ++i) {
        Point pA = poly[i];
        Point pB = poly[(i + 1) % n];
        bool straddles_y = (pA.y > mid_y) != (pB.y > mid_y);

        if (straddles_y) {
            double intersect_x = pA.x + (mid_y - pA.y) * (pB.x - pA.x) / (double)(pB.y - pA.y);
            if (mid_x < intersect_x) { intersections++; }
        }
    }

    // Even = outside, odd = inside
    return (intersections % 2 != 0);
}

std::vector<Point> parse_points(const std::vector<std::string>& lines) {
    std::vector<Point> points;

    for (const auto& line : lines) {
        size_t comma_pos = line.find(',');

        if (comma_pos != std::string::npos) {
            Point p;
            p.x = std::stoi(line.substr(0, comma_pos));
            p.y = std::stoi(line.substr(comma_pos + 1));

            points.push_back(p);
        }
    }
    return points;
}

void part1(const std::vector<std::string>& lines) {
    auto points = parse_points(lines);
    long long max_area = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            const Point& p1 = points[i];
            const Point& p2 = points[j];

            long long width = std::abs(p1.x - p2.x) + 1;
            long long height = std::abs(p1.y - p2.y) + 1;
            long long area = width * height;

            if (area > max_area) { max_area = area; }
        }
    }

    std::cout << "Part 1: Largest area: " << max_area << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    auto points = parse_points(lines);
    long long max_area = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            const Point& p1 = points[i];
            const Point& p2 = points[j];

            if (is_valid_rectangle(p1, p2, points)) {
                long long width = std::abs(p1.x - p2.x) + 1;
                long long height = std::abs(p1.y - p2.y) + 1;
                long long area = width * height;

                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }

    std::cout << "Part 2: Largest valid area: " << max_area << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day09.txt");

    part1(lines);
    part2(lines);

    return 0;
}
