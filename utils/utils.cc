#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

using Matrix = std::vector<std::vector<std::string>>;

namespace aoc {
namespace utils {

void ReadFile(
    std::string path, std::string& file_contents) {
    std::ifstream file(path);
    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    file_contents = absl::StrJoin(lines, "\n");
}

void ReadFileByLine(
    const std::string path,
    std::function<void(std::string)> callback) {
    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            callback(line);
        }

        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

std::vector<std::vector<std::string>> ReadFileAsMatrix(
    const std::string path) {
    std::vector<std::vector<std::string>> matrix;

    aoc::utils::ReadFileByLine(path, [&](std::string line) {
        matrix.push_back(absl::StrSplit(line, ""));
    });

    return matrix;
}

bool InBounds(Matrix& matrix, int i, int j) {
    return i >= 0 && i < matrix.size() && j >= 0 && j < matrix[0].size();
}

}  // namespace utils

}  // namespace aoc