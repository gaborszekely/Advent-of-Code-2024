#include <iostream>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "utils/utils.h"

constexpr char kInputPath[] = "day8/input.txt";

using namespace aoc::utils;

/*
HashMap
char -> std::vector<Coord>
*/

bool IsAntenna(const std::string& val) {
    return val != ".";
}

void PopulateAntennaCoordsMap(const Matrix<std::string>& matrix, absl::flat_hash_map<std::string, std::vector<Coord>>& map) {
    const std::size_t r = matrix.size();
    const std::size_t c = matrix[0].size();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (IsAntenna(matrix[i][j])) {
                map[matrix[i][j]].push_back({i, j});
            }
        }
    }
}

int PartOne() {
    const auto matrix = ReadFileAsMatrix(kInputPath);
    absl::flat_hash_map<std::string, std::vector<Coord>> map;
    PopulateAntennaCoordsMap(matrix, map);

    absl::flat_hash_set<Coord> seen;

    for (const auto& [key, coords] : map) {
        const int size = coords.size();
        for (int i = 0; i < size - 1; ++i) {
            for (int j = i + 1; j < size; ++j) {
                const auto& [firstX, firstY] = coords[i];
                const auto& [secondX, secondY] = coords[j];
                const int xDiff = secondX - firstX;
                const int yDiff = secondY - firstY;

                // check first direction
                if (InBounds(matrix, firstX - xDiff, firstY - yDiff)) {
                    seen.insert({firstX - xDiff, firstY - yDiff});
                }

                // check second direction
                if (InBounds(matrix, secondX + xDiff, secondY + yDiff)) {
                    seen.insert({secondX + xDiff, secondY + yDiff});
                }
            }
        }
    }

    return seen.size();
}

int PartTwo() {
    const auto matrix = ReadFileAsMatrix(kInputPath);
    absl::flat_hash_map<std::string, std::vector<Coord>> map;
    PopulateAntennaCoordsMap(matrix, map);

    absl::flat_hash_set<Coord> seen;

    for (const auto& [key, coords] : map) {
        const int size = coords.size();
        for (int i = 0; i < size - 1; ++i) {
            for (int j = i + 1; j < size; ++j) {
                const auto& [firstX, firstY] = coords[i];
                const auto& [secondX, secondY] = coords[j];

                seen.insert(coords[i]);
                seen.insert(coords[j]);

                const int xDiff = secondX - firstX;
                const int yDiff = secondY - firstY;

                // check first direction
                int newX = firstX - xDiff;
                int newY = firstY - yDiff;

                while (InBounds(matrix, newX, newY)) {
                    seen.insert({newX, newY});
                    newX -= xDiff;
                    newY -= yDiff;
                }

                // check second direction
                newX = secondX + xDiff;
                newY = secondY + yDiff;

                while (InBounds(matrix, newX, newY)) {
                    seen.insert({newX, newY});
                    newX += xDiff;
                    newY += yDiff;
                }
            }
        }
    }

    return seen.size();
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
