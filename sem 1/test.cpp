#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include "catch.hpp"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>

#include "bubble_sort.h"
#include "exchange_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "optimized_bubble_sort.h"

using namespace std;

bool arrays_equal(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Bubble Sort", "[bubble_sort]") {
    SECTION("Single element") {
        int arr[] = { 5 };
        int expected[] = { 5 };
        bubble_sort(arr, 1);
        REQUIRE(arrays_equal(arr, expected, 1));
    }

    SECTION("Sorted array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int expected[] = { 1, 2, 3, 4, 5 };
        bubble_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Reverse sorted") {
        int arr[] = { 5, 4, 3, 2, 1 };
        int expected[] = { 1, 2, 3, 4, 5 };
        bubble_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Random array") {
        int arr[] = { 3, 1, 4, 1, 5, 9, 2 };
        int expected[] = { 1, 1, 2, 3, 4, 5, 9 };
        bubble_sort(arr, 7);
        REQUIRE(arrays_equal(arr, expected, 7));
    }
}

TEST_CASE("Exchange Sort", "[exchange_sort]") {
    SECTION("Single element") {
        int arr[] = { 5 };
        int expected[] = { 5 };
        exchange_sort(arr, 1);
        REQUIRE(arrays_equal(arr, expected, 1));
    }

    SECTION("Sorted array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int expected[] = { 1, 2, 3, 4, 5 };
        exchange_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Reverse sorted") {
        int arr[] = { 5, 4, 3, 2, 1 };
        int expected[] = { 1, 2, 3, 4, 5 };
        exchange_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }
}

TEST_CASE("Insertion Sort", "[insertion_sort]") {
    SECTION("Single element") {
        int arr[] = { 5 };
        int expected[] = { 5 };
        insertion_sort(arr, 1);
        REQUIRE(arrays_equal(arr, expected, 1));
    }

    SECTION("Sorted array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int expected[] = { 1, 2, 3, 4, 5 };
        insertion_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Random array") {
        int arr[] = { 3, 1, 4, 1, 5, 9, 2 };
        int expected[] = { 1, 1, 2, 3, 4, 5, 9 };
        insertion_sort(arr, 7);
        REQUIRE(arrays_equal(arr, expected, 7));
    }
}

TEST_CASE("Optimized Bubble Sort", "[optimized_bubble_sort]") {
    SECTION("Single element") {
        int arr[] = { 5 };
        int expected[] = { 5 };
        optimized_bubble_sort(arr, 1);
        REQUIRE(arrays_equal(arr, expected, 1));
    }

    SECTION("Sorted array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int expected[] = { 1, 2, 3, 4, 5 };
        optimized_bubble_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Reverse sorted") {
        int arr[] = { 5, 4, 3, 2, 1 };
        int expected[] = { 1, 2, 3, 4, 5 };
        optimized_bubble_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }
}

TEST_CASE("Selection Sort", "[selection_sort]") {
    SECTION("Single element") {
        int arr[] = { 5 };
        int expected[] = { 5 };
        selection_sort(arr, 1);
        REQUIRE(arrays_equal(arr, expected, 1));
    }

    SECTION("Sorted array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int expected[] = { 1, 2, 3, 4, 5 };
        selection_sort(arr, 5);
        REQUIRE(arrays_equal(arr, expected, 5));
    }

    SECTION("Random array") {
        int arr[] = { 3, 1, 4, 1, 5, 9, 2 };
        int expected[] = { 1, 1, 2, 3, 4, 5, 9 };
        selection_sort(arr, 7);
        REQUIRE(arrays_equal(arr, expected, 7));
    }
}

TEST_CASE("All methods comparison", "[all]") {
    int test_array[] = { 3, 1, 4, 1, 5, 9, 2 };
    int expected[] = { 1, 1, 2, 3, 4, 5, 9 };
    int size = 7;

    int arr1[] = { 3, 1, 4, 1, 5, 9, 2 };
    int arr2[] = { 3, 1, 4, 1, 5, 9, 2 };
    int arr3[] = { 3, 1, 4, 1, 5, 9, 2 };
    int arr4[] = { 3, 1, 4, 1, 5, 9, 2 };
    int arr5[] = { 3, 1, 4, 1, 5, 9, 2 };

    bubble_sort(arr1, size);
    exchange_sort(arr2, size);
    insertion_sort(arr3, size);
    optimized_bubble_sort(arr4, size);
    selection_sort(arr5, size);

    REQUIRE(arrays_equal(arr1, expected, size));
    REQUIRE(arrays_equal(arr2, expected, size));
    REQUIRE(arrays_equal(arr3, expected, size));
    REQUIRE(arrays_equal(arr4, expected, size));
    REQUIRE(arrays_equal(arr5, expected, size));
}