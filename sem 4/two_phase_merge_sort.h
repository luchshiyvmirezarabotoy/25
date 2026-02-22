#ifndef TWO_PHASE_MERGE_SORT_H
#define TWO_PHASE_MERGE_SORT_H

#include <string>
#include <functional>

template<typename T>
class TwoPhaseMergeSort {
public:
    void sort(const std::string& input_file, const std::string& output_file,
        std::function<bool(const T&, const T&)> comparator = std::less<T>());

private:
    bool distribute_series(const std::string& input_file,
        const std::string& file_a, const std::string& file_b,
        std::function<bool(const T&, const T&)> comparator);
    void merge_series(const std::string& file_a, const std::string& file_b,
        const std::string& output_file,
        std::function<bool(const T&, const T&)> comparator);
    bool copy_file(const std::string& src, const std::string& dst);
};

#endif