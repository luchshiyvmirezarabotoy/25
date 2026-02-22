#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <vector>

namespace Sort {
    template <typename T>
    void shellSort(std::vector<T>& arr);
}

#include "shell_sort.cpp"

#endif