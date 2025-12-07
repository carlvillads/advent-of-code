#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <set>
#include "input_reader.h"

using namespace std;

struct Position {
    size_t row;
    size_t col;

    bool operator<(const Position& other) const {
        return tie(row, col) < tie(other.row, other.col);
    }
};

vector<Position> generateCoordinateSystem(const vector<string>& lines) {
    vector<Position> rollLocations;
    size_t rowCount = 0;

    for (const auto& line : lines) {
        for (size_t col = 0; col < line.length(); ++col) {
            if (line[col] == '@') {
                rollLocations.push_back({rowCount, col});
            }
        }
        rowCount++;
    }

    return rollLocations;
}

void part1(const vector<string>& lines) {
    int rollsAccessable = 0;
    vector<Position> rollLocations = generateCoordinateSystem(lines);
    set<Position> warehouseLookup(rollLocations.begin(), rollLocations.end());

    // relative coordinates
    const long long relRows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const long long relCols[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (const auto& pos : rollLocations) {
        int neighborCount = 0;

        // check all 8 neighbors
        for (int i = 0; i < 8; ++i) {
            long long checkRows = (long long)pos.row + relRows[i];
            long long checkCols = (long long)pos.col + relCols[i];

            if (checkRows >= 0 && checkCols >= 0) {
                Position neighbor = {(size_t)checkRows, (size_t)checkCols};

                if (warehouseLookup.count(neighbor)) {
                    neighborCount++;
                }
            }
        }

        if (neighborCount < 4) { rollsAccessable++; }
    }


    cout << rollsAccessable << " rolls of paper can be accessed in the diagram." << endl;
}

void part2(const vector<string>& lines) {
    vector<Position> rollLocations = generateCoordinateSystem(lines);
    set<Position> warehouseLookup(rollLocations.begin(), rollLocations.end());

    int totalRemoved = 0;
    bool rollsWereRemoved = true;

    const long long relRows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const long long relCols[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (rollsWereRemoved) {
        rollsWereRemoved = false;
        vector<Position> toRemove;

        for (const auto& pos : warehouseLookup) {
            int neighborCount = 0;

            for (int i = 0; i < 8; ++i) {
                long long checkRows = (long long)pos.row + relRows[i];
                long long checkCols = (long long)pos.col + relCols[i];

                if (checkRows >= 0 && checkCols >= 0) {
                    Position neighbor = {(size_t)checkRows, (size_t)checkCols};

                    if (warehouseLookup.count(neighbor)) { neighborCount++; }
                }
            }

            if (neighborCount < 4) { toRemove.push_back(pos); }
        }

        if (!toRemove.empty()) {
            rollsWereRemoved = true;
            totalRemoved += toRemove.size();

            for (const auto& p : toRemove) { warehouseLookup.erase(p); }
        }
    }

    cout << totalRemoved << " total rolls of paper can be removed." << endl;
}

int main() {
    auto lines = readInput("../inputs/day04.txt");

    part1(lines);
    part2(lines);

    return 0;
}
