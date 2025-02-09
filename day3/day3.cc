#include <iostream>
#include <regex>
#include <string>

#include "utils/utils.h"

constexpr char kInputPath[] = "day3/input.txt";

int GetMultiplicationResult(std::string expression) {
    std::regex pattern("mul\\((\\d+),(\\d+)\\)");
    std::smatch matches;

    if (std::regex_search(expression, matches, pattern)) {
        return std::stoi(matches[1]) * std::stoi(matches[2]);
    }

    throw std::runtime_error("Invalid expression");
}

int PartOne() {
    std::regex pattern("mul\\(\\d+,\\d+\\)");
    std::smatch match;

    std::string text;
    aoc::utils::ReadFile(kInputPath, text);

    std::string::const_iterator searchStart(text.cbegin());

    int total = 0;

    while (std::regex_search(searchStart, text.cend(), match, pattern)) {
        total += GetMultiplicationResult(match.str());
        searchStart = match.suffix().first;
    }

    return total;
}

int PartTwo() {
    std::regex pattern("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
    std::smatch match;

    std::string text;
    aoc::utils::ReadFile(kInputPath, text);

    std::string::const_iterator searchStart(text.cbegin());

    int total = 0;
    bool enabled = true;

    while (std::regex_search(searchStart, text.cend(), match, pattern)) {
        std::string match_text = match.str();

        if (match_text == "do()") {
            enabled = true;
        } else if (match_text == "don't()") {
            enabled = false;
        } else if (enabled) {
            total += GetMultiplicationResult(match_text);
        }
        searchStart = match.suffix().first;
    }

    return total;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
