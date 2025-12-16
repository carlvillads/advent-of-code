#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include "input_reader.h"

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

long long count_paths_recursive(const std::string& current, const std::string& target, 
                                Graph& graph, std::unordered_map<std::string, long long>& memo) {
    
    if (current == target) {
        return 1;
    }

    // Check memoization
    if (memo.count(current)) {
        return memo[current];
    }

    long long total = 0;

    if (graph.count(current)) {
        for (const auto& neighbor : graph[current]) {
            total += count_paths_recursive(neighbor, target, graph, memo);
        }
    }

    return memo[current] = total;
}

long long count_segment(const std::string& start, const std::string& end, Graph& graph) {
    std::unordered_map<std::string, long long> memo;
    return count_paths_recursive(start, end, graph, memo);
}

Graph parse_input(const std::vector<std::string>& lines) {
    Graph graph;
    for (const auto& line : lines) {
        if (line.empty()) continue;
        size_t colon_pos = line.find(':');
        std::string src = line.substr(0, colon_pos);
        std::string dests_str = line.substr(colon_pos + 2); 
        std::stringstream ss(dests_str);
        std::string dest;
        while (ss >> dest) {
            graph[src].push_back(dest);
        }
    }
    return graph;
}

void part1(const std::vector<std::string>& lines) {
    Graph graph = parse_input(lines);
    long long result = count_segment("you", "out", graph);
    std::cout << "Part 1: " << result << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    Graph graph = parse_input(lines);

    // svr -> dac -> fft -> out
    // svr -> fft -> dac -> out

    long long svr_to_dac = count_segment("svr", "dac", graph);
    long long dac_to_fft = count_segment("dac", "fft", graph);
    long long fft_to_out = count_segment("fft", "out", graph);

    long long path1_total = svr_to_dac * dac_to_fft * fft_to_out;

    long long svr_to_fft = count_segment("svr", "fft", graph);
    long long fft_to_dac = count_segment("fft", "dac", graph);
    long long dac_to_out = count_segment("dac", "out", graph);

    long long path2_total = svr_to_fft * fft_to_dac * dac_to_out;

    long long total_valid_paths = path1_total + path2_total;

    std::cout << "Part 2: " << total_valid_paths << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day11.txt");

    part1(lines);
    part2(lines);

    return 0;
}
