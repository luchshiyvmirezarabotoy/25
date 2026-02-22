#ifndef ONE_PHASE_MERGE_SORT_H
#define ONE_PHASE_MERGE_SORT_H

#include <string>
#include <functional>
#include <vector>

template<typename T>
class OnePhaseMergeSort {
public:
    void sort(const std::string& input_file, const std::string& output_file,
        size_t memory_limit = 1000,
        std::function<bool(const T&, const T&)> comparator = std::less<T>());

private:
    void create_initial_runs(const std::string& input_file,
        const std::vector<std::string>& temp_files,
        size_t memory_limit,
        std::function<bool(const T&, const T&)> comparator);
    void merge_files(const std::vector<std::string>& input_files,
        const std::string& output_file,
        std::function<bool(const T&, const T&)> comparator);
};

#endif