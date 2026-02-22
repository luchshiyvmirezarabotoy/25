#include <iostream>
#include <vector>
#include "quick_sort.h"
#include "shell_sort.h"

int main() {
    
    std::cout << "Quick Sort:" << std::endl;
    std::vector<int> quick_arr = { 14, 6, 12, 18, 5, 1, 11, 3 };
    std::cout << "Bef: ";
    for (int num : quick_arr) std::cout << num << " ";
    Sort::quickSort(quick_arr);
    std::cout << "\nAfter: ";
    for (int num : quick_arr) std::cout << num << " ";
    std::cout << "\n" << std::endl;


    std::cout << "Shell Sort:" << std::endl;
    std::vector<int> shell_arr = { 14, 6, 12, 18, 5, 1, 11, 3 };
    std::cout << "Bef: ";
    for (int num : shell_arr) std::cout << num << " ";
    Sort::shellSort(shell_arr);
    std::cout << "\nAfter: ";
    for (int num : shell_arr) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}