#include "one_phase_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <string>

template<typename T>
void OnePhaseMergeSort<T>::sort(const std::string& input_file,
    const std::string& output_file,
    size_t memory_limit,
    std::function<bool(const T&, const T&)> comparator) {
    std::vector<std::string> temp_files;
    for (int i = 0; i < 4; ++i) {
        temp_files.push_back("temp_" + std::to_string(i) + ".bin");
    }


    create_initial_runs(input_file, temp_files, memory_limit, comparator);


    merge_files(temp_files, output_file, comparator);


    for (const auto& file : temp_files) {
        std::remove(file.c_str());
    }
}

template<typename T>
void OnePhaseMergeSort<T>::create_initial_runs(const std::string& input_file,
    const std::vector<std::string>& temp_files,
    size_t memory_limit,
    std::function<bool(const T&, const T&)> comparator) {
    std::ifstream input(input_file, std::ios::binary);
    if (!input) throw std::runtime_error("Cannot open input file");

    std::vector<std::ofstream> outputs;
    for (const auto& file : temp_files) {
        outputs.emplace_back(file, std::ios::binary);
        if (!outputs.back()) {
            throw std::runtime_error("Cannot create temp file: " + file);
        }
    }

    std::vector<T> buffer;
    buffer.reserve(memory_limit);
    T value;
    size_t current_file = 0;

    while (input.read(reinterpret_cast<char*>(&value), sizeof(T))) {
        buffer.push_back(value);

        if (buffer.size() >= memory_limit) {
            std::sort(buffer.begin(), buffer.end(), comparator);

            for (const auto& item : buffer) {
                outputs[current_file].write(reinterpret_cast<const char*>(&item), sizeof(T));
            }

            buffer.clear();
            current_file = (current_file + 1) % temp_files.size();
        }
    }

    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end(), comparator);
        for (const auto& item : buffer) {
            outputs[current_file].write(reinterpret_cast<const char*>(&item), sizeof(T));
        }
    }

    for (auto& stream : outputs) {
        stream.close();
    }

    input.close();
}

template<typename T>
void OnePhaseMergeSort<T>::merge_files(const std::vector<std::string>& input_files,
    const std::string& output_file,
    std::function<bool(const T&, const T&)> comparator) {
    struct QueueItem {
        T value;
        size_t file_index;
    };

 
    auto comp = [comparator](const QueueItem& a, const QueueItem& b) {
       
        return !(comparator(a.value, b.value));
        };


    std::priority_queue<QueueItem, std::vector<QueueItem>, decltype(comp)> pq(comp);
    std::vector<std::ifstream> inputs;
    inputs.reserve(input_files.size());


    for (size_t i = 0; i < input_files.size(); ++i) {
        inputs.emplace_back(input_files[i], std::ios::binary);
        if (!inputs.back()) {
            throw std::runtime_error("Cannot open temp file for reading: " + input_files[i]);
        }

        T value;
        if (inputs[i].read(reinterpret_cast<char*>(&value), sizeof(T))) {
            pq.push({ value, i });
        }
    }

    std::ofstream output(output_file, std::ios::binary);
    if (!output) {
        throw std::runtime_error("Cannot open output file: " + output_file);
    }

 
    while (!pq.empty()) {
        auto item = pq.top();
        pq.pop();

        output.write(reinterpret_cast<const char*>(&item.value), sizeof(T));

        T next_value;
        if (inputs[item.file_index].read(reinterpret_cast<char*>(&next_value), sizeof(T))) {
            pq.push({ next_value, item.file_index });
        }
    }

    for (auto& input_stream : inputs) {
        input_stream.close();
    }
    output.close();
}

template class OnePhaseMergeSort<int>;
template class OnePhaseMergeSort<double>;
template class OnePhaseMergeSort<float>;