#include <iostream>
#include <fstream>
#include <vector>
#include "two_phase_merge_sort.h"
#include "one_phase_merge_sort.h"
#include "natural_merge_sort.h"

int main() {
    std::vector<int> numbers = { 14, 6, 12, 18, 5, 1, 11, 3 };


    std::cout << "Def: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    std::ofstream input("numbers.bin", std::ios::binary);
    for (int num : numbers) {
        input.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }
    input.close();


    std::cout << "1. Two-Phase Merge Sort Result:\n";
    TwoPhaseMergeSort<int> sorter1;
    sorter1.sort("numbers.bin", "sorted1.bin");

    std::ifstream result1("sorted1.bin", std::ios::binary);
    int value;
    while (result1.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        std::cout << value << " ";
    }
    result1.close();
    std::cout << "\n\n";

    std::cout << "2. One-Phase Merge Sort Result:\n";
    OnePhaseMergeSort<int> sorter2;
    sorter2.sort("numbers.bin", "sorted2.bin", 4);

    std::ifstream result2("sorted2.bin", std::ios::binary);
    while (result2.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        std::cout << value << " ";
    }
    result2.close();
    std::cout << "\n\n";

    std::cout << "3. Natural Merge Sort Result:\n";
    NaturalMergeSort<int> sorter3;
    sorter3.sort("numbers.bin", "sorted3.bin");

    std::ifstream result3("sorted3.bin", std::ios::binary);
    while (result3.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        std::cout << value << " ";
    }
    result3.close();
    std::cout << "\n\n";

    std::remove("numbers.bin");
    std::remove("sorted1.bin");
    std::remove("sorted2.bin");
    std::remove("sorted3.bin");



    return 0;
}