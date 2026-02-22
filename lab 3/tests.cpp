#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.h"
#include "lists.h"
#include <vector>

TEST_CASE("DoubleList bubbleSort works correctly", "[DoubleList]") {
    DoubleList<int> list;

    // Заполняем список неотсортированными данными
    list.push_back(5);
    list.push_back(2);
    list.push_back(9);
    list.push_back(1);
    list.push_back(5);
    list.push_back(6);

    // Применяем сортировку пузырьком
    list.bubbleSort();

    // Проверяем, что список отсортирован
    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    auto it = list.begin();
    for (int val : expected) {
        REQUIRE(*it == val);
        ++it;
    }
}

TEST_CASE("DoubleList shellSort works correctly", "[DoubleList]") {
    DoubleList<int> list;

    // Заполняем список неотсортированными данными
    list.push_back(5);
    list.push_back(2);
    list.push_back(9);
    list.push_back(1);
    list.push_back(5);
    list.push_back(6);

    // Применяем сортировку Шелла
    list.shellSort();

    // Проверяем, что список отсортирован
    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    auto it = list.begin();
    for (int val : expected) {
        REQUIRE(*it == val);
        ++it;
    }
}
