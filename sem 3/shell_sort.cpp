#ifndef SHELL_SORT_CPP
#define SHELL_SORT_CPP

#include <vector>

namespace Sort {

    template <typename T>
    void shellSort(std::vector<T>& arr) {
        int n = arr.size();
        
        for (int gap = n / 2; gap > 0; gap /= 2) {
            
            for (int i = gap; i < n; i += 1) {
                T temp = arr[i];
                int j;
                
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                
                arr[j] = temp;
            }
        }
    }

}

#endif