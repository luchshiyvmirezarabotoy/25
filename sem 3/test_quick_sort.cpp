#include "catch.h"
#include "quick_sort.h"

TEST_CASE("Quick Sort: Integers", "[quick_sort]") {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    Sort::quickSort(arr);
    REQUIRE(arr == std::vector<int>{1, 5, 7, 8, 9, 10});
}

TEST_CASE("Quick Sort: Negative Numbers", "[quick_sort]") {
    std::vector<int> arr = {-1, -5, 0, 10, 2};
    Sort::quickSort(arr);
    REQUIRE(arr == std::vector<int>{-5, -1, 0, 2, 10});
}

TEST_CASE("Quick Sort: Edge Cases", "[quick_sort]") {
    SECTION("One Element") {
        std::vector<int> arr = {42};
        Sort::quickSort(arr);
        REQUIRE(arr == std::vector<int>{42});
    }

    SECTION("Duplicates") {
        std::vector<int> arr = {4, 2, 4, 2};
        Sort::quickSort(arr);
        REQUIRE(arr == std::vector<int>{2, 2, 4, 4});
    }

    SECTION("Large Gap") {
         std::vector<int> arr = {1000, 1};
         Sort::quickSort(arr);
         REQUIRE(arr == std::vector<int>{1, 1000});
    }
}