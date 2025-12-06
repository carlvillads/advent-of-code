#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <set>
#include "input_reader.h"

struct IDRange {
    long long start;
    long long end;

    bool operator<(const IDRange& other) const {
        return start < other.start;
    }
};

std::vector<IDRange> getMergedRanges(const std::vector<std::string>& lines) {
    std::vector<IDRange> ranges;

    for (const auto& line : lines) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string segment;

        while (std::getline(ss, segment, ',')) {
            size_t dashPos = segment.find('-');
            if (dashPos != std::string::npos) {
                try {
                    long long start = std::stoll(segment.substr(0, dashPos));
                    long long end = std::stoll(segment.substr(dashPos + 1));
                    ranges.push_back({start, end});
                } catch (...) { continue; }
            }
        }
    }

    if (ranges.empty()) return {};

    std::sort(ranges.begin(), ranges.end());
    std::vector<IDRange> mergedRanges;
    mergedRanges.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); ++i) {
        if (ranges[i].start <= mergedRanges.back().end + 1) {
            mergedRanges.back().end = std::max(mergedRanges.back().end, ranges[i].end);
        } else {
            mergedRanges.push_back(ranges[i]);
        }
    }
    return mergedRanges;
}

unsigned long long sumSequence(long long start, long long end) {
    if (start > end) { return 0; }
    unsigned long long count = (unsigned long long)(end - start + 1);
    unsigned long long sum = (unsigned long long)(start + end);
    return (count * sum) / 2;
}


void part1(const std::vector<std::string>& lines) {
    std::vector<IDRange> mergedRanges = getMergedRanges(lines);
    unsigned long long totalInvalidSum = 0;

    for (const auto& r : mergedRanges) {
        long long A = r.start;
        long long B = r.end;

        for (int L = 2; L <= 18; L += 2) {
            long long halfLen = L / 2;
            
            unsigned long long powerOf10 = 1;
            for(int k=0; k<halfLen; ++k) powerOf10 *= 10;
            unsigned long long F = powerOf10 + 1;

            long long minS_digits = powerOf10 / 10;
            long long maxS_digits = powerOf10 - 1;

            long long minS_range = (A + F - 1) / F; 
            long long maxS_range = B / F;           

            long long startS = std::max(minS_digits, minS_range);
            long long endS = std::min(maxS_digits, maxS_range);

            if (startS <= endS) {
                unsigned long long sumS = sumSequence(startS, endS);
                totalInvalidSum += sumS * F;
            }
        }
    }

    std::cout << "Part 1 Answer: " << totalInvalidSum << std::endl;
}

void part2(const std::vector<std::string>& lines) {
    std::vector<IDRange> mergedRanges = getMergedRanges(lines);
    std::set<long long> uniqueInvalidIDs;

    for (int L = 1; L <= 9; ++L) {
        
        // Iterate Repeat Counts (k)
        for (int k = 2; k <= 18; ++k) {
            if (L * k > 18) break;

            unsigned long long shift = 1;
            for(int i=0; i<L; ++i) shift *= 10;

            unsigned long long F = 0;
            unsigned long long currentTerm = 1;
            for(int i=0; i<k; ++i) {
                F += currentTerm;
                currentTerm *= shift;
            }

            long long minP_digits = shift / 10;
            long long maxP_digits = shift - 1;

            for (const auto& r : mergedRanges) {
                long long minP_range = (r.start + F - 1) / F; // Ceil division
                long long maxP_range = r.end / F;             // Floor division

                long long startP = std::max(minP_digits, minP_range);
                long long endP = std::min(maxP_digits, maxP_range);

                for (long long p = startP; p <= endP; ++p) {
                    uniqueInvalidIDs.insert(p * F);
                }
            }
        }
    }

    unsigned long long totalInvalidSum = 0;
    for (long long id : uniqueInvalidIDs) {
        totalInvalidSum += id;
    }

    std::cout << "Part 2 Answer: " << totalInvalidSum << std::endl;
}

int main() {
    auto lines = readInput("../inputs/day02.txt");

    part1(lines);
    part2(lines);

    return 0;
}