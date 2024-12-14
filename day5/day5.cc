#include <iostream>
#include <regex>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "utils/utils.h"

using namespace aoc::utils;
const std::string kInputPath = "day5/input.txt";

std::vector<std::vector<int>> GetOutOfOrderRows() {
}

int PartOne() {
    absl::flat_hash_map<int, absl::flat_hash_set<int>> succeeding_values_map;
    bool has_split = false;
    int result = 0;

    ReadFileByLine(kInputPath, [&](std::string line) {
        if (line == "") {
            has_split = true;
            return;
        }

        if (!has_split) {
            std::regex pattern("(\\d+)\\|(\\d+)");
            std::smatch matches;

            if (std::regex_search(line, matches, pattern)) {
                auto preceding_value = std::stoi(matches[1]);
                auto value = std::stoi(matches[2]);
                succeeding_values_map[preceding_value].insert(value);
            } else {
                throw std::runtime_error("Invalid expression");
            }
        } else {
            std::vector<std::string> row = absl::StrSplit(line, ",");
            std::vector<int> values;
            std::transform(row.begin(), row.end(), std::back_inserter(values),
                           [](const std::string& str) { return std::stoi(str); });

            absl::flat_hash_set<int> seen_values;

            for (std::size_t i = 0; i < values.size(); i++) {
                const auto& succeeding_values = succeeding_values_map[values[i]];

                for (int succeeding_value : succeeding_values) {
                    if (seen_values.contains(succeeding_value)) {
                        return;
                    }
                }

                seen_values.insert(values[i]);
            }

            result += values[values.size() / 2];
        }
    });

    return result;
}

using ValuesMap = absl::flat_hash_map<int, absl::flat_hash_set<int>>;

// void Recurse(int value, ValuesMap& preceding_values_map, absl::flat_hash_set<int>& seen_indexes, std::vector<int>& result) {
//     if ()
//         const auto& preceding_values = preceding_values_map[value];
// }
// std::vector<int> TopoSort(std::vector<int>& values, ValuesMap& preceding_values_map) {
//     std::vector<int> result;
//     absl::flat_hash_set<int> seen_indexes;

//     for (auto& [value, preceding_values] : preceding_values_map) {
//         Recurse(value, preceding_values_map, seen_indexes, result);
//     }

//     return result;
// }

int PartTwo() {
    ValuesMap succeeding_values_map;
    ValuesMap preceding_values_map;
    bool has_split = false;
    int result = 0;

    ReadFileByLine(kInputPath, [&](std::string line) {
        if (line == "") {
            has_split = true;
            return;
        }

        if (!has_split) {
            std::regex pattern("(\\d+)\\|(\\d+)");
            std::smatch matches;

            if (std::regex_search(line, matches, pattern)) {
                auto preceding_value = std::stoi(matches[1]);
                auto value = std::stoi(matches[2]);
                succeeding_values_map[preceding_value].insert(value);
                preceding_values_map[value].insert(preceding_value);
                preceding_values_map[preceding_value];
            } else {
                throw std::runtime_error("Invalid expression");
            }
        } else {
            // std::vector<std::string> row = absl::StrSplit(line, ",");
            // std::vector<int> values;
            // std::transform(row.begin(), row.end(), std::back_inserter(values),
            //                [](const std::string& str) { return std::stoi(str); });

            // absl::flat_hash_set<int> seen_values;

            // for (std::size_t i = 0; i < values.size(); i++) {
            //     const auto& succeeding_values = succeeding_values_map[values[i]];

            //     for (int succeeding_value : succeeding_values) {
            //         if (seen_values.contains(succeeding_value)) {
            //             // const auto& sorted = TopoSort(values, preceding_values_map);
            //             // result += sorted[sorted.size() / 2];
            //             return;
            //         }
            //     }

            //     seen_values.insert(values[i]);
            // }
        }
    });

    for (const auto& [preceding_value, succeeding_values] : succeeding_values_map) {
        std::cout << preceding_value << ": " << absl::StrJoin(succeeding_values, ",") << std::endl;
        std::cout << "------------------" << std::endl;
    }

    std::cout << "=====================================" << std::endl;

    std::vector<std::pair<int, absl::flat_hash_set<int>>> sorted;

    for (auto& it : preceding_values_map) {
        sorted.push_back(it);
    }

    // Sort using comparator function
    sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second.size() > b.second.size(); });

    std::cout << sorted.size() << std::endl;
    for (const auto& [key, value] : sorted) {
        std::cout << key << ": " << value.size() << std::endl;
        std::cout << "------------------" << std::endl;
    }

    return result;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
