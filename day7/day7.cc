#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <regex>

#include "absl/strings/str_split.h"
#include "utils/utils.h"

const std::string kInputPath = "day7/input.txt";

using namespace aoc::utils;
using namespace boost::multiprecision;

bool CanMakeTarget(std::vector<long> &nums, long &target, int i, long res) {
    if (i == nums.size()) {
        return res == target;
    }

    return CanMakeTarget(nums, target, i + 1, res + nums[i]) ||
           CanMakeTarget(nums, target, i + 1, res * nums[i]);
}

bool CanMakeTarget2(std::vector<long> &nums, cpp_int &target, int i, cpp_int res) {
    if (i == nums.size()) {
        return res == target;
    }

    return CanMakeTarget2(nums, target, i + 1, res + nums[i]) ||
           CanMakeTarget2(nums, target, i + 1, res * nums[i]) ||
           CanMakeTarget2(nums, target, i + 1, cpp_int(res.str() + std::to_string(nums[i])));
}

long PartOne() {
    long result = 0;

    ReadFileByLine(kInputPath, [&result](std::string line) {
        std::regex pattern("(\\d+):\\s(.+)");
        std::smatch matches;

        if (std::regex_search(line, matches, pattern)) {
            long target = std::stol(matches[1]);
            std::vector<long> nums = ConvertToLongs(absl::StrSplit(matches[2].str(), " "));

            if (CanMakeTarget(nums, target, 1, nums[0])) {
                result += target;
            }

        } else {
            throw std::runtime_error("Invalid expression");
        }
    });

    return result;
}

cpp_int PartTwo() {
    cpp_int result = 0;

    ReadFileByLine(kInputPath, [&result](std::string line) {
        std::regex pattern("(\\d+):\\s(.+)");
        std::smatch matches;

        if (std::regex_search(line, matches, pattern)) {
            auto target = cpp_int(matches[1].str());
            std::vector<long> nums = ConvertToLongs(absl::StrSplit(matches[2].str(), " "));

            if (CanMakeTarget2(nums, target, 1, cpp_int(nums[0]))) {
                result += target;
            }

        } else {
            throw std::runtime_error("Invalid expression");
        }
    });

    return result;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
