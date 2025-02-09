#include <iostream>

#include "absl/container/flat_hash_map.h"
#include "utils/utils.h"

constexpr char kInputPath[] = "day6/input.txt";

using namespace aoc::utils;

std::pair<int, int> GetStartingCoords(Matrix<std::string>& matrix) {
    std::size_t r = matrix.size();
    std::size_t c = matrix[0].size();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == "^") {
                return {i, j};
            }
        }
    }
    throw new std::runtime_error("Could not find starting coords");
}

std::pair<int, int> GetNextCoords(const Matrix<std::string>& matrix, const std::pair<int, int>& starting_coords, int direction) {
    // up
    if (direction == 0) {
        return {starting_coords.first - 1, starting_coords.second};
    }
    // right
    if (direction == 1) {
        return {starting_coords.first, starting_coords.second + 1};
    }
    // down
    if (direction == 2) {
        return {starting_coords.first + 1, starting_coords.second};
    }
    // left
    if (direction == 3) {
        return {starting_coords.first, starting_coords.second - 1};
    }
    throw new std::runtime_error("Invalid direction");
}

bool InBounds(int i, int j, int r, int c) {
    return i >= 0 && i < r && j >= 0 && j < c;
}

int PartOne() {
    auto matrix = ReadFileAsMatrix(kInputPath);
    auto current_coords = GetStartingCoords(matrix);
    std::size_t r = matrix.size();
    std::size_t c = matrix[0].size();

    // 0 = up, 1 = right, 2 = down, 3 = left
    int direction = 0;
    int count = 1;

    while (true) {
        if (matrix[current_coords.first][current_coords.second] == ".") {
            count++;
        }
        matrix[current_coords.first][current_coords.second] = "x";
        std::pair<int, int> next_coords = GetNextCoords(matrix, current_coords, direction);
        if (!InBounds(next_coords.first, next_coords.second, r, c)) {
            break;
        }

        while (matrix[next_coords.first][next_coords.second] == "#") {
            direction = (direction + 1) % 4;
            next_coords = GetNextCoords(matrix, current_coords, direction);
        }

        current_coords = next_coords;
    }

    return count;
}

// std::lower_bound is used to find first element that is greater than or equal to the given value.
// std::upper_bound is used to find first element that is greater than the given value.

std::optional<std::pair<int, int>> GetNextBarrierCoords(
    const Matrix<std::string>& matrix,
    absl::flat_hash_map<int, std::vector<int>>& row_map,
    absl::flat_hash_map<int, std::vector<int>>& col_map,
    const std::pair<int, int>& starting_coords,
    const int& direction) {
    // up
    if (direction == 0) {
        auto v = col_map[starting_coords.second];
        // Find the first element not less than target
        auto it = std::lower_bound(v.begin(), v.end(), starting_coords.first);

        if (it == v.begin()) {
            return std::nullopt;
        } else {
            --it;  // Move to the previous element
            return std::make_pair(*it, starting_coords.second);
        }
    }

    // right
    if (direction == 1) {
        auto v = row_map[starting_coords.first];
        // Find the first element greater than target
        auto it = std::upper_bound(v.begin(), v.end(), starting_coords.second);

        if (it == v.begin()) {
            return std::nullopt;
        } else {
            return std::make_pair(starting_coords.first, *it);
        }
    }

    // down
    if (direction == 2) {
        auto v = col_map[starting_coords.second];
        // Find the first element greater than target
        auto it = std::upper_bound(v.begin(), v.end(), starting_coords.first);

        if (it == v.begin()) {
            return std::nullopt;
        } else {
            return std::make_pair(*it, starting_coords.second);
        }
    }

    // left
    if (direction == 3) {
        auto v = row_map[starting_coords.first];
        // Find the first element not less than target
        auto it = std::lower_bound(v.begin(), v.end(), starting_coords.second);

        if (it == v.begin()) {
            return std::nullopt;
        } else {
            --it;  // Move to the previous element
            return std::make_pair(starting_coords.first, *it);
        }
    }
}

int PartTwo() {
    // Map (row) -> sorted list of col cells
    absl::flat_hash_map<int, std::vector<int>> row_map;
    // Map (col) -> sorted list of row cells
    absl::flat_hash_map<int, std::vector<int>> col_map;

    auto matrix = ReadFileAsMatrix(kInputPath);

    std::size_t r = matrix.size();
    std::size_t c = matrix[0].size();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == "#") {
                row_map[i].push_back(j);
                col_map[j].push_back(i);
            }
        }
    }

    return 0;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
