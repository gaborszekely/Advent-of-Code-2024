#include <iostream>

#include "absl/strings/string_view.h"
#include "utils/utils.h"

using namespace aoc::utils;

constexpr char kInputPath[] = "day4/input.txt";

int CheckXmas(
    const Matrix<std::string>& matrix,
    int r,
    int c,
    absl::string_view marker,
    const std::vector<const int>& next_coords_delta) {
    for (int i = 0; i < marker.size(); i++) {
        if (!InBounds(matrix, r, c) || matrix[r][c][0] != marker[i]) {
            return 0;
        }
        r += next_coords_delta[0];
        c += next_coords_delta[1];
    }
    return 1;
}

int PartOne() {
    constexpr absl::string_view kXmasMarker = "XMAS";
    const std::vector<const std::vector<const int>> kCoordsDeltas = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

    auto matrix = ReadFileAsMatrix(kInputPath);
    int r = matrix.size();
    int c = matrix[0].size();
    int result = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (matrix[i][j] == "X") {
                for (const auto& coords_delta : kCoordsDeltas) {
                    if (CheckXmas(matrix, i, j, kXmasMarker, coords_delta)) {
                        result += 1;
                    }
                }
            }
        }
    }

    return result;
}

int PartTwo() {
    constexpr absl::string_view kMasMarker = "MAS";
    const std::vector<const std::vector<const int>> kDiagonalCoordsDeltas = {
        {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

    auto matrix = ReadFileAsMatrix(kInputPath);
    int r = matrix.size();
    int c = matrix[0].size();
    int result = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (matrix[i][j] == "M") {
                for (const auto& coords_delta : kDiagonalCoordsDeltas) {
                    if (CheckXmas(matrix, i, j, kMasMarker, coords_delta)) {
                        if (
                            CheckXmas(matrix, (i + 2 * coords_delta[0]), j, kMasMarker, {coords_delta[0] * -1, coords_delta[1]}) ||
                            CheckXmas(matrix, i, (j + 2 * coords_delta[1]), kMasMarker, {coords_delta[0], coords_delta[1] * -1})) {
                            result++;
                        }
                    }
                }
            }
        }
    }

    return result / 2;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
