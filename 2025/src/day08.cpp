#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <numeric>

#include "input_reader.h"

struct Point {
    int id;
    long long x, y, z;
};

struct Edge {
    int u;
    int v;
    long long dist_sq;
};

// Disjoint Set Union
struct DSU {
    std::vector<int> parent;
    std::vector<int> size;
    int num_components;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        std::iota(parent.begin(), parent.end(), 0);
        num_components = n;
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) {
                std::swap(root_i, root_j);
            }

            parent[root_j] = root_i;
            size[root_i] += size[root_j];

            num_components--;
            return true;
        }
        return false;
    }
};

std::vector<Point> parse_points(const std::vector<std::string>& lines) {
    std::vector<Point> points;

    for (int i = 0; i < lines.size(); ++i) {
        std::stringstream ss(lines[i]);
        std::string segment;
        std::vector<long long> coords;

        while (std::getline(ss, segment, ',')) {
            coords.push_back(std::stoll(segment));
        }
        if (coords.size() >= 3) {
            points.push_back({i, coords[0], coords[1], coords[2]});
        }
    }
    return points;
}

std::vector<Edge> get_sorted_edges(const std::vector<Point>& points) {
    std::vector<Edge> edges;
    int n = points.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = points[i].x - points[j].x;
            long long dy = points[i].y - points[j].y;
            long long dz = points[i].z - points[j].z;
            long long dist_sq = dx*dx + dy*dy + dz*dz;

            edges.push_back({i, j, dist_sq});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.dist_sq < b.dist_sq;
    });
    
    return edges;
}

void part1(const std::vector<Point>& points, const std::vector<Edge>& edges) {
    int n = points.size();
    DSU dsu(n);
    int limit = std::min((int)edges.size(), 1000);

    for (int i = 0; i < limit; ++i) {
        dsu.unite(edges[i].u, edges[i].v);
    }

    std::vector<int> circuit_sizes;
    for (int i = 0; i < n; ++i) {
        if (dsu.parent[i] == i) {
            circuit_sizes.push_back(dsu.size[i]);
        }
    }

    std::sort(circuit_sizes.rbegin(), circuit_sizes.rend());

    long long answer = 0;
    if (circuit_sizes.size() >= 3) {
        answer = (long long)circuit_sizes[0] * circuit_sizes[1] * circuit_sizes[2];
    } else {
        answer = 1;
        for(int s : circuit_sizes) answer *= s;
    }

    std::cout << "Part 1: " << answer << std::endl;
}

void part2(const std::vector<Point>& points, const std::vector<Edge>& edges) {
    int n = points.size();
    DSU dsu(n);
    long long answer = 0;

    for (const auto& edge : edges) {
        bool merged = dsu.unite(edge.u, edge.v);

        if (merged) {
            if (dsu.num_components == 1) {
                long long x1 = points[edge.u].x;
                long long x2 = points[edge.v].x;
                answer = x1 * x2;

                std::cout << "Final connection between " << edge.u << " and " << edge.v << std::endl;
                break;
            }
        }
    }
    

    std::cout << "Part 2: " << answer << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day08.txt");

    auto points = parse_points(lines);
    auto edges = get_sorted_edges(points);

    part1(points, edges);
    part2(points, edges);

    return 0;
}
