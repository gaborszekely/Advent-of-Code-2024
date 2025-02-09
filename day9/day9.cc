#include <iostream>
#include <numeric>

#include "absl/strings/str_split.h"
#include "utils/utils.h"

constexpr char kInputPath[] = "day9/input.txt";

using namespace aoc::utils;

long long PartOne() {
    std::string file_contents;
    ReadFile(kInputPath, file_contents);
    auto disk_map = ConvertToInts(absl::StrSplit(file_contents, ""));
    const int disk_map_size = disk_map.size();

    int slots = 0;
    for (int i = 0; i < disk_map_size; i += 2) {
        slots += disk_map[i];
    }

    long long checksum = 0;
    int disk_map_index = 0;
    int slot_index = 0;
    int move_index = disk_map_size - 1;

    // calculate checksum
    while (slot_index < slots) {
        if (disk_map_index % 2 == 0) {
            int id = disk_map_index / 2;
            for (int i = 0; i < disk_map[disk_map_index]; ++i) {
                checksum += (long long)slot_index * (long long)id;
                slot_index++;
            }
        } else {
            for (int i = 0; i < disk_map[disk_map_index]; ++i) {
                if (disk_map[move_index] == 0) {
                    move_index -= 2;
                }
                int move_index_id = move_index / 2;
                checksum += (long long)move_index_id * (long long)slot_index;
                disk_map[move_index]--;
                slot_index++;
            }
        }
        disk_map_index++;
    }

    return checksum;
}

long long PartTwo() {
    std::string file_contents;
    ReadFile(kInputPath, file_contents);
    auto disk_map = ConvertToInts(absl::StrSplit(file_contents, ""));
    const int disk_map_size = disk_map.size();

    long long checksum = 0;
    return checksum;
}

int main() {
    std::cout << PartOne() << std::endl;
    std::cout << PartTwo() << std::endl;
    return 0;
}
