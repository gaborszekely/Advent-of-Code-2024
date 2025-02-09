#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

namespace aoc {
namespace utils {

using Matrix = std::vector<std::vector<std::string>>;
using Coord = std::pair<int, int>;

void ReadFile(
    const std::string path, std::string& file_contents) {
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

std::vector<int> ConvertToInts(const std::vector<std::string> input) {
    std::vector<int> nums;

    for (std::size_t i = 0; i < input.size(); i++) {
        nums.push_back(std::stoi(input[i]));
    }

    return nums;
}

std::vector<long> ConvertToLongs(const std::vector<std::string> input) {
    std::vector<long> nums;

    for (std::size_t i = 0; i < input.size(); i++) {
        nums.push_back(std::stol(input[i]));
    }

    return nums;
}

const std::array<const std::array<int, 2>, 4>* GetCardinalNeighborDeltas() {
    static const std::array<const std::array<int, 2>, 4> deltas = {{{0, 1},
                                                                    {1, 0},
                                                                    {0, -1},
                                                                    {-1, 0}}};

    return &deltas;
}

}  // namespace utils

}  // namespace aoc