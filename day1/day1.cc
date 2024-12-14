#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "utils/utils.h"

const std::string kInputPath = "day1/input.txt";

int PartOne() {
    std::vector<int> list_one;
    std::vector<int> list_two;

    aoc::utils::ReadFileByLine(kInputPath, [&](std::string line) {
        std::pair<std::string, std::string> line_items = absl::StrSplit(line, "   ");
        list_one.push_back(std::stoi(line_items.first));
        list_two.push_back(std::stoi(line_items.second));
    });

    std::sort(list_one.begin(), list_one.end());
    std::sort(list_two.begin(), list_two.end());

    int result = 0;
    for (std::size_t i = 0; i < list_one.size(); i++) {
        result += std::abs(list_one[i] - list_two[i]);
    }

    return result;
}

int PartTwo() {
    std::vector<int> list_one;
    absl::flat_hash_map<int, int> list_two_counts;

    aoc::utils::ReadFileByLine(kInputPath, [&](std::string line) {
        std::pair<std::string, std::string> line_items = absl::StrSplit(line, "   ");
        list_one.push_back(std::stoi(line_items.first));
        list_two_counts[std::stoi(line_items.second)] += 1;
    });

    int result = 0;
    for (int num : list_one) {
        result += num * list_two_counts[num];
    }

    return result;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}