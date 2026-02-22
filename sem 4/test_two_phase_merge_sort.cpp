#include "catch_amalgamated.h"
#include "two_phase_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

TEST_CASE("TwoPhaseMergeSort - empty file") {
    TwoPhaseMergeSort<int> sorter;


    std::ofstream out("empty_input.bin", std::ios::binary);
    out.close();

    REQUIRE_NOTHROW(sorter.sort("empty_input.bin", "empty_output.bin"));

 
    std::ifstream in("empty_output.bin", std::ios::binary);
    in.seekg(0, std::ios::end);
    REQUIRE(in.tellg() == 0);

    std::remove("empty_input.bin");
    std::remove("empty_output.bin");
}

TEST_CASE("TwoPhaseMergeSort - single element") {
    TwoPhaseMergeSort<int> sorter;


    std::ofstream out("single_input.bin", std::ios::binary);
    int value = 42;
    out.write(reinterpret_cast<char*>(&value), sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("single_input.bin", "single_output.bin"));

    std::ifstream in("single_output.bin", std::ios::binary);
    int result;
    in.read(reinterpret_cast<char*>(&result), sizeof(int));
    REQUIRE(result == 42);
    REQUIRE(in.peek() == EOF);

    std::remove("single_input.bin");
    std::remove("single_output.bin");
}

TEST_CASE("TwoPhaseMergeSort - sorted array") {
    TwoPhaseMergeSort<int> sorter;


    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::ofstream out("sorted_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("sorted_input.bin", "sorted_output.bin"));


    std::ifstream in("sorted_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == data);

    std::remove("sorted_input.bin");
    std::remove("sorted_output.bin");
}

TEST_CASE("TwoPhaseMergeSort - reverse sorted array") {
    TwoPhaseMergeSort<int> sorter;


    std::vector<int> data = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::ofstream out("reverse_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("reverse_input.bin", "reverse_output.bin"));


    std::ifstream in("reverse_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(result == expected);

    std::remove("reverse_input.bin");
    std::remove("reverse_output.bin");
}

TEST_CASE("TwoPhaseMergeSort - random array") {
    TwoPhaseMergeSort<int> sorter;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    std::vector<int> data(1000);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

    std::ofstream out("random_input.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(int));
    out.close();

    REQUIRE_NOTHROW(sorter.sort("random_input.bin", "random_output.bin"));

 
    std::ifstream in("random_output.bin", std::ios::binary);
    std::vector<int> result(data.size());
    in.read(reinterpret_cast<char*>(result.data()), result.size() * sizeof(int));

    REQUIRE(std::is_sorted(result.begin(), result.end()));


    std::sort(data.begin(), data.end());
    REQUIRE(result == data);

    std::remove("random_input.bin");
    std::remove("random_output.bin");
}