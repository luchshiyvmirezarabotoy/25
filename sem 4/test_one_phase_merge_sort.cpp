#include "catch_amalgamated.h"
#include "one_phase_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

TEST_CASE("OnePhaseMergeSort - empty file") {
    OnePhaseMergeSort<int> sorter;

    std::ofstream out("empty_input.bin", std::ios::binary);
    out.close();

    REQUIRE_NOTHROW(sorter.sort("empty_input.bin", "empty_output.bin", 100));

    std::ifstream in("empty_output.bin", std::ios::binary);
    in.seekg(0, std::ios::end);
    REQUIRE(in.tellg() == 0);

    std::remove("empty_input.bin");
    std::remove("empty_output.bin");
}

TEST_CASE("OnePhaseMergeSort - small memory limit") {
    OnePhaseMergeSort<int> sorter;

    std::vector<int> data = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> expected = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::ofstream out("small_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("small_input.bin", "small_output.bin", 2));

    std::ifstream in("small_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == expected);

    std::remove("small_input.bin");
    std::remove("small_output.bin");
}

TEST_CASE("OnePhaseMergeSort - already sorted") {
    OnePhaseMergeSort<int> sorter;

    std::vector<int> data;
    for (int i = 0; i < 100; ++i) {
        data.push_back(i);
    }

    std::ofstream out("sorted_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("sorted_input.bin", "sorted_output.bin", 10));

    std::ifstream in("sorted_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == data);

    std::remove("sorted_input.bin");
    std::remove("sorted_output.bin");
}

TEST_CASE("OnePhaseMergeSort - large random data") {
    OnePhaseMergeSort<int> sorter;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    std::vector<int> data(5000);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

    std::ofstream out("large_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("large_input.bin", "large_output.bin", 100));

    std::ifstream in("large_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(std::is_sorted(result.begin(), result.end()));

    std::sort(data.begin(), data.end());
    REQUIRE(result == data);

    std::remove("large_input.bin");
    std::remove("large_output.bin");
}