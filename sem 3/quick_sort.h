#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>

namespace Sort {
    template <typename T>
    void quickSort(std::vector<T>& arr);
}

#include "quick_sort.cpp"

#endif