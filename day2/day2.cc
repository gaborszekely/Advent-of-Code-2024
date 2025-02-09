#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "utils/utils.h"

constexpr char kInputPath[] = "day2/input.txt";

bool CountSafeReports(int& result, std::function<bool(std::vector<int>&)> check_report_safety) {
    int i = 0;

    aoc::utils::ReadFileByLine(kInputPath, [&](std::string line) {
        std::vector<std::string> raw_levels = absl::StrSplit(line, " ");
        std::vector<int> report;

        for (std::size_t i = 0; i < raw_levels.size(); i++) {
            report.push_back(std::stoi(raw_levels[i]));
        }

        if (check_report_safety(report)) {
            result++;
        }

        i++;
    });

    return result;
}

bool IsValidDiff(int diff) {
    return diff == 1 || diff == 3;
}

bool IsValidIncreasing(int prev, int curr) {
    return IsValidDiff(curr - prev);
}

bool IsValidDecreasing(int prev, int curr) {
    return IsValidDiff(prev - curr);
}

bool IsSafeReport(std::vector<int>& report) {
    bool is_increasing = report[1] > report[0];

    for (std::size_t i = 1; i < report.size(); i++) {
        if (is_increasing) {
            int diff = report[i] - report[i - 1];
            if (report[i] <= report[i - 1] || diff < 1 || diff > 3) {
                return false;
            }
        } else {
            int diff = report[i - 1] - report[i];
            if (report[i] >= report[i - 1] || diff < 1 || diff > 3) {
                return false;
            }
        }
    }

    return true;
}

int PartOne() {
    int result = 0;
    CountSafeReports(result, IsSafeReport);

    return result;
}

int PartTwo() {
    int result = 0;

    CountSafeReports(result, [](std::vector<int>& report) {
        if (IsSafeReport(report)) {
            return true;
        }

        for (std::size_t i = 0; i < report.size(); i++) {
            std::vector<int> copy = report;
            copy.erase(copy.begin() + i);
            if (IsSafeReport(copy)) {
                return true;
            }
        }

        return false;
    });

    return result;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}