#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "input_reader.h"

using namespace std;

int findMaxJoltage(const vector<int>& bank) {
    int maxJoltage = -1;

    for (size_t i = 0; i < bank.size(); ++i) {
        for (size_t j = i + 1; j < bank.size(); ++j) {
            int currentJoltage = (bank[i] * 10) + bank[j];  // shift left by multiplying by 10

            if (currentJoltage > maxJoltage) { maxJoltage = currentJoltage; }
        }
    }

    return maxJoltage;
}

long long greedyMaxJoltage(const vector<int>& bank) {
    int to_skip = bank.size() - 12;  // the max number of elements we can skip
    vector<int> stack;

    for (int battery : bank) {
        while (!stack.empty() && to_skip > 0 && stack.back() < battery) {
            stack.pop_back();  // remove the smaller battery
            to_skip--;         // use an allowed skip
        }
        stack.push_back(battery);
    }

    stack.resize(12);  // in case all skips werent used

    long long maxJoltage = 0;
    for (int digit : stack) { maxJoltage = (maxJoltage * 10) + digit; }

    return maxJoltage;
}

void part1(const vector<string>& lines) {
    int totalJoltageOutput = 0;
    
    for (const auto& line : lines) {
        vector<int> bank;
        transform(line.begin(), line.end(), back_inserter(bank), 
        [](char c) { return c - '0'; });  // convert line into vector<int>

        int maxBankJoltage = findMaxJoltage(bank);
        totalJoltageOutput += maxBankJoltage;
    }

    cout << "The max total joltage output is: " << totalJoltageOutput << endl;
}

void part2(const vector<string>& lines) {
    long long totalJoltageOutput = 0;
    
    for (const auto& line : lines) {
        vector<int> bank;
        transform(line.begin(), line.end(), back_inserter(bank), 
        [](char c) { return c - '0'; });

        long long maxBankJoltage = greedyMaxJoltage(bank);
        totalJoltageOutput += maxBankJoltage;
    }

    cout << "The max total joltage output with 12 batteries/bank is: " << totalJoltageOutput << endl;
}

int main() {
    auto lines = readInput("../inputs/day03.txt");

    part1(lines);
    part2(lines);

    return 0;
}
