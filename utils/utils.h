#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

namespace aoc {
namespace utils {

using Matrix = std::vector<std::vector<std::string>>;
using Coord = std::pair<int, int>;

void ReadFile(
    std::string path, std::string& file_contents);

void ReadFileByLine(
    const std::string path,
    std::function<void(std::string)> callback);

std::vector<std::vector<std::string>> ReadFileAsMatrix(
    const std::string path);

bool InBounds(Matrix& matrix, int i, int j);

std::vector<int> ConvertToInts(std::vector<std::string> input);

std::vector<long> ConvertToLongs(std::vector<std::string> input);

}  // namespace utils

}  // namespace aoc