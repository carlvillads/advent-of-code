#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

static std::vector<std::string> readInput(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: could not open file: " << filename << std::endl;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

#endif // INPUT_READER_H
