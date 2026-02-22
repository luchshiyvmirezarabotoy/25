#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "shell_sort.h"

TEST_CASE("Shell Sort: Integers", "[shell_sort]") {
    std::vector<int> arr = {9, 8, 3, 7, 5, 6, 4, 1};
    Sort::shellSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 4, 5, 6, 7, 8, 9});
}

TEST_CASE("Shell Sort: Doubles", "[shell_sort]") {
    std::vector<double> arr = {2.5, 1.1, 3.7};
    Sort::shellSort(arr);
    REQUIRE(arr == std::vector<double>{1.1, 2.5, 3.7});
}

TEST_CASE("Shell Sort: Edge Cases", "[shell_sort]") {
    SECTION("Empty Array") {
        std::vector<int> arr;
        Sort::shellSort(arr);
        REQUIRE(arr.empty());
    }

    SECTION("Sorted Array") {
        std::vector<int> arr = {1, 2, 3};
        Sort::shellSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3});
    }

    SECTION("Reverse Array") {
        std::vector<int> arr = {3, 2, 1};
        Sort::shellSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3});
    }
}