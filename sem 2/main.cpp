#include <iostream>
#include <vector>
#include "binary_insertion_sort.h"
#include "shaker_sort.h"

template<typename T>
void printArray(const std::vector<T>& arr, const std::string& algorithmName) {
    std::cout << algorithmName << ": ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
int main() {
    std::vector<int> original = { 14, 6, 12, 18, 5, 1, 11, 3 };

    std::cout << "Better algo" << std::endl;
    for (const auto& elem : original) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> arr1 = original;
    binary_insertion_sort(arr1);
    printArray(arr1, "Binary Insertion Sort");

    std::vector<int> arr2 = original;
    shaker_sort(arr2);
    printArray(arr2, "Shaker Sort");

    std::cout << std::endl << "Default result: 1 3 5 6 11 12 14 18" << std::endl;

    return 0;
}