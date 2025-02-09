#include <iostream>
#include <map>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "utils/utils.h"

using namespace aoc::utils;

constexpr char kInputPath[] = "day10/input.txt";

// A map of starting trailhead -> set of reachable peaks
using ReachablePeaksMap = absl::flat_hash_map<std::pair<int, int>, absl::flat_hash_set<std::pair<int, int>>>;

// For each trailhead, finds the number of peaks that can be reached from that trailhead.
void FindReachablePeaks(const Matrix<int>& matrix, const int& sr, const int& sc, const int r, const int c, ReachablePeaksMap& reachable_peaks_map, int& result) {
    if (matrix[r][c] == 9) {
        if (!reachable_peaks_map[{sr, sc}].contains({r, c})) {
            reachable_peaks_map[{sr, sc}].insert({r, c});
            result++;
        }
        return;
    }

    const auto deltas = GetCardinalNeighborDeltas();

    for (const auto& [dr, dc] : *deltas) {
        const int nr = r + dr;
        const int nc = c + dc;

        if (InBounds(matrix, nr, nc) && matrix[nr][nc] == matrix[r][c] + 1) {
            FindReachablePeaks(matrix, sr, sc, nr, nc, reachable_peaks_map, result);
        }
    }
}

// Finds the total number of distinct hiking paths starting from a given trailhead.
void FindPaths(const Matrix<int>& matrix, const int& sr, const int& sc, const int r, const int c, int& result) {
    if (matrix[r][c] == 9) {
        result++;
        return;
    }

    const auto deltas = GetCardinalNeighborDeltas();

    for (const auto& [dr, dc] : *deltas) {
        const int nr = r + dr;
        const int nc = c + dc;

        if (InBounds(matrix, nr, nc) && matrix[nr][nc] == matrix[r][c] + 1) {
            FindPaths(matrix, sr, sc, nr, nc, result);
        }
    }
}

int PartOne() {
    const auto matrix = ReadFileAsMatrix<int>(kInputPath, [](char c) {
        return c - '0';
    });

    const int r = matrix.size();
    const int c = matrix[0].size();
    int result = 0;
    ReachablePeaksMap reachable_peaks_map;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == 0) {
                FindReachablePeaks(matrix, i, j, i, j, reachable_peaks_map, result);
            }
        }
    }

    return result;
}

int PartTwo() {
    const auto matrix = ReadFileAsMatrix<int>(kInputPath, [](char c) {
        return c - '0';
    });

    const int r = matrix.size();
    const int c = matrix[0].size();
    int result = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == 0) {
                FindPaths(matrix, i, j, i, j, result);
            }
        }
    }

    return result;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
