#include "natural_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
void NaturalMergeSort<T>::sort(const std::string& input_file,
    const std::string& output_file,
    std::function<bool(const T&, const T&)> comparator) {
    std::string file_a = "temp_nat_a.bin";
    std::string file_b = "temp_nat_b.bin";

    size_t series_count;
    bool use_input_as_output = false;

    do {
        if (!use_input_as_output) {
            series_count = distribute_natural_series(input_file, file_a, file_b, comparator);
            merge_series(file_a, file_b, output_file, comparator);
        }
        else {
            series_count = distribute_natural_series(output_file, file_a, file_b, comparator);
            merge_series(file_a, file_b, input_file, comparator);
        }

        use_input_as_output = !use_input_as_output;
    } while (series_count > 1);


    if (use_input_as_output) {
        std::ifstream src(input_file, std::ios::binary);
        std::ofstream dst(output_file, std::ios::binary);
        dst << src.rdbuf();
    }

    std::remove(file_a.c_str());
    std::remove(file_b.c_str());
}

template<typename T>
size_t NaturalMergeSort<T>::distribute_natural_series(const std::string& input_file,
    const std::string& file_a,
    const std::string& file_b,
    std::function<bool(const T&, const T&)> comparator) {
    std::ifstream input(input_file, std::ios::binary);
    std::ofstream a(file_a, std::ios::binary);
    std::ofstream b(file_b, std::ios::binary);

    if (!input || !a || !b) {
        throw std::runtime_error("Cannot open files for natural distribution");
    }

    T current, next;
    bool to_a = true;
    size_t series_count = 0;

    if (!input.read(reinterpret_cast<char*>(&current), sizeof(T))) {
        return 0; 
    }

    a.write(reinterpret_cast<char*>(&current), sizeof(T));
    series_count++;

    while (input.read(reinterpret_cast<char*>(&next), sizeof(T))) {
  
        if (comparator(next, current)) {
            to_a = !to_a;
            series_count++;
        }

        if (to_a) {
            a.write(reinterpret_cast<char*>(&next), sizeof(T));
        }
        else {
            b.write(reinterpret_cast<char*>(&next), sizeof(T));
        }

        current = next;
    }

    return series_count;
}

template<typename T>
void NaturalMergeSort<T>::merge_series(const std::string& file_a,
    const std::string& file_b,
    const std::string& output_file,
    std::function<bool(const T&, const T&)> comparator) {
    std::ifstream a(file_a, std::ios::binary);
    std::ifstream b(file_b, std::ios::binary);
    std::ofstream output(output_file, std::ios::binary);

    if (!a || !b || !output) {
        throw std::runtime_error("Cannot open files for natural merging");
    }

    T a_val, b_val;
    bool a_end = !a.read(reinterpret_cast<char*>(&a_val), sizeof(T));
    bool b_end = !b.read(reinterpret_cast<char*>(&b_val), sizeof(T));
    bool a_series_end = false;
    bool b_series_end = false;

    while (!a_end || !b_end) {
        bool from_a;

        if (a_end || a_series_end) {
            from_a = false;
        }
        else if (b_end || b_series_end) {
            from_a = true;
        }
        else {
            from_a = !comparator(b_val, a_val);
        }

        if (from_a) {
            output.write(reinterpret_cast<char*>(&a_val), sizeof(T));
            T prev = a_val;
            a_end = !a.read(reinterpret_cast<char*>(&a_val), sizeof(T));
            a_series_end = a_end || comparator(a_val, prev);
        }
        else {
            output.write(reinterpret_cast<char*>(&b_val), sizeof(T));
            T prev = b_val;
            b_end = !b.read(reinterpret_cast<char*>(&b_val), sizeof(T));
            b_series_end = b_end || comparator(b_val, prev);
        }


        if (a_series_end && b_series_end) {
            a_series_end = false;
            b_series_end = false;
        }
    }
}

template class NaturalMergeSort<int>;
template class NaturalMergeSort<double>;
template class NaturalMergeSort<float>;