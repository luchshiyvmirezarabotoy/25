#include "catch_amalgamated.h"
#include "natural_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

TEST_CASE("NaturalMergeSort - empty file") {
    NaturalMergeSort<int> sorter;

    std::ofstream out("empty_input.bin", std::ios::binary);
    out.close();

    REQUIRE_NOTHROW(sorter.sort("empty_input.bin", "empty_output.bin"));

    std::ifstream in("empty_output.bin", std::ios::binary);
    in.seekg(0, std::ios::end);
    REQUIRE(in.tellg() == 0);

    std::remove("empty_input.bin");
    std::remove("empty_output.bin");
}

TEST_CASE("NaturalMergeSort - single element") {
    NaturalMergeSort<int> sorter;

    std::ofstream out("single_input.bin", std::ios::binary);
    int value = 77;
    out.write(reinterpret_cast<char*>(&value), sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("single_input.bin", "single_output.bin"));

    std::ifstream in("single_output.bin", std::ios::binary);
    int result;
    in.read(reinterpret_cast<char*>(&result), sizeof(int));
    REQUIRE(result == 77);

    std::remove("single_input.bin");
    std::remove("single_output.bin");
}

TEST_CASE("NaturalMergeSort - partially sorted") {
    NaturalMergeSort<int> sorter;


    std::vector<int> data = { 1, 2, 3, 9, 8, 7, 4, 5, 6, 10, 11, 12 };
    std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    std::ofstream out("partial_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("partial_input.bin", "partial_output.bin"));

    std::ifstream in("partial_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == expected);

    std::remove("partial_input.bin");
    std::remove("partial_output.bin");
}

TEST_CASE("NaturalMergeSort - all elements equal") {
    NaturalMergeSort<int> sorter;

    std::vector<int> data(100, 5); 

    std::ofstream out("equal_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("equal_input.bin", "equal_output.bin"));

    std::ifstream in("equal_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == data);

    std::remove("equal_input.bin");
    std::remove("equal_output.bin");
}

TEST_CASE("NaturalMergeSort - descending order") {
    NaturalMergeSort<int> sorter;

    std::vector<int> data;
    for (int i = 100; i > 0; --i) {
        data.push_back(i);
    }

    std::vector<int> expected;
    for (int i = 1; i <= 100; ++i) {
        expected.push_back(i);
    }

    std::ofstream out("desc_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("desc_input.bin", "desc_output.bin"));

    std::ifstream in("desc_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == expected);

    std::remove("desc_input.bin");
    std::remove("desc_output.bin");
}