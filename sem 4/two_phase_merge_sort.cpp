#include "two_phase_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
void TwoPhaseMergeSort<T>::sort(const std::string& input_file,
    const std::string& output_file,
    std::function<bool(const T&, const T&)> comparator) {
    std::string file_a = "temp_a.bin";
    std::string file_b = "temp_b.bin";

    bool sorted = false;
    int phase = 0;

    while (!sorted) {
        if (phase % 2 == 0) {
            sorted = distribute_series(input_file, file_a, file_b, comparator);
            merge_series(file_a, file_b, output_file, comparator);
        }
        else {
            sorted = distribute_series(output_file, file_a, file_b, comparator);
            merge_series(file_a, file_b, input_file, comparator);
        }
        phase++;
    }

    if (phase % 2 == 0) {
        copy_file(input_file, output_file);
    }

    std::remove(file_a.c_str());
    std::remove(file_b.c_str());
}

template<typename T>
bool TwoPhaseMergeSort<T>::distribute_series(const std::string& input_file,
    const std::string& file_a,
    const std::string& file_b,
    std::function<bool(const T&, const T&)> comparator) {
    std::ifstream input(input_file, std::ios::binary);
    std::ofstream a(file_a, std::ios::binary);
    std::ofstream b(file_b, std::ios::binary);

    if (!input || !a || !b) {
        throw std::runtime_error("Cannot open files for distribution");
    }

    T current, next;
    bool to_a = true;
    size_t series_count = 0;

    if (!input.read(reinterpret_cast<char*>(&current), sizeof(T))) {
        return true;
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

    return series_count <= 1;
}

template<typename T>
void TwoPhaseMergeSort<T>::merge_series(const std::string& file_a,
    const std::string& file_b,
    const std::string& output_file,
    std::function<bool(const T&, const T&)> comparator) {
    std::ifstream a(file_a, std::ios::binary);
    std::ifstream b(file_b, std::ios::binary);
    std::ofstream output(output_file, std::ios::binary);

    if (!a || !b || !output) {
        throw std::runtime_error("Cannot open files for merging");
    }

    T a_val, b_val;
    bool a_end = !a.read(reinterpret_cast<char*>(&a_val), sizeof(T));
    bool b_end = !b.read(reinterpret_cast<char*>(&b_val), sizeof(T));

    while (!a_end || !b_end) {
        bool from_a;

        if (a_end) {
            from_a = false;
        }
        else if (b_end) {
            from_a = true;
        }
        else {
            from_a = !comparator(b_val, a_val);
        }

        if (from_a) {
            output.write(reinterpret_cast<char*>(&a_val), sizeof(T));
            a_end = !a.read(reinterpret_cast<char*>(&a_val), sizeof(T));
        }
        else {
            output.write(reinterpret_cast<char*>(&b_val), sizeof(T));
            b_end = !b.read(reinterpret_cast<char*>(&b_val), sizeof(T));
        }
    }
}

template<typename T>
bool TwoPhaseMergeSort<T>::copy_file(const std::string& src, const std::string& dst) {
    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dst, std::ios::binary);

    if (!input || !output) return false;

    output << input.rdbuf();
    return true;
}


template class TwoPhaseMergeSort<int>;
template class TwoPhaseMergeSort<double>;
template class TwoPhaseMergeSort<float>;