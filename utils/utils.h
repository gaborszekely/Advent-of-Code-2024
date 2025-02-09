#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "absl/strings/str_split.h"

namespace aoc {
namespace utils {

template <typename T = std::string>
using Matrix = std::vector<std::vector<T>>;

using Coord = std::pair<int, int>;

void ReadFile(
    std::string path, std::string& file_contents);

void ReadFileByLine(
    const std::string path,
    std::function<void(std::string)> callback);

/**
 * Reads a file as a matrix. Can return a matrix of any type using a user-provided mapper function.
 */
template <typename T = std::string>
Matrix<T> ReadFileAsMatrix(
    const std::string& path,
    std::function<T(char)> mapper_fn = [](char c) {
        return static_cast<T>(c);
    }) {
    Matrix<T> matrix;

    aoc::utils::ReadFileByLine(path, [&](std::string line) {
        std::vector<std::string> chars = absl::StrSplit(line, "");
        std::vector<T> row;

        for (std::string c : chars) {
            row.push_back(mapper_fn(c[0]));
        }

        matrix.push_back(row);
    });

    return matrix;
}

template <typename T = std::string>
bool InBounds(const Matrix<T>& matrix, const int& i, const int& j) {
    return i >= 0 && i < matrix.size() && j >= 0 && j < matrix[0].size();
}

std::vector<int> ConvertToInts(std::vector<std::string> input);

std::vector<long> ConvertToLongs(std::vector<std::string> input);

const std::array<const std::array<int, 2>, 4>* GetCardinalNeighborDeltas();

}  // namespace utils

}  // namespace aoc