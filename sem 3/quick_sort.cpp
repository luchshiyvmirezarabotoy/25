#ifndef QUICK_SORT_CPP
#define QUICK_SORT_CPP

#include <vector>
#include <algorithm>

namespace Sort {

    template <typename T>
    int partition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high]; 
        int i = (low - 1); 

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    template <typename T>
    void quickSortRecursive(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);

            quickSortRecursive(arr, low, pi - 1);
            quickSortRecursive(arr, pi + 1, high);
        }
    }

    template <typename T>
    void quickSort(std::vector<T>& arr) {
        if (arr.empty()) return;
        quickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1);
    }

}

#endif