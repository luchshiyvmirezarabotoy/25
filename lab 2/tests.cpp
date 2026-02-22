#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.h"
#include <string>
#include <cctype>

// Функция для обработки строки согласно заданию
std::string processString(const std::string& str) {
    std::string result;

    for (size_t i = 0; i < str.length(); i++) {
        char currentChar = str[i];

        // Проверяем, является ли символ цифрой
        if (isdigit(currentChar)) {
            int digit = currentChar - '0';

            if (digit % 2 == 0) {
                // Четная цифра
                if (i < str.length() - 1) {
                    // Не последний символ - добавляем цифру и "++"
                    result += currentChar;
                    result += "++";
                }
                else {
                    // Последний символ - просто добавляем цифру
                    result += currentChar;
                }
            } // Нечетные цифры пропускаем (не добавляем в результат)
        }
        else {
            // Не цифра - просто копируем
            result += currentChar;
        }
    }

    return result;
}

// ТЕСТЫ
TEST_CASE("Обработка строк с четными цифрами") {
    SECTION("Четная цифра не последняя") {
        CHECK(processString("a2b") == "a2++b");
        CHECK(processString("4c") == "4++c");
        CHECK(processString("x8y8z") == "x8++y8++z");
    }

    SECTION("Четная цифра последняя") {
        CHECK(processString("ab4") == "ab4");
        CHECK(processString("6") == "6");
        CHECK(processString("x2y4") == "x2++y4");
    }

    SECTION("Несколько четных цифр") {
        CHECK(processString("2a4b6") == "2++a4++b6");
        CHECK(processString("28c4") == "2++8++c4");
    }
}

TEST_CASE("Обработка строк с нечетными цифрами") {
    SECTION("Нечетные цифры удаляются") {
        CHECK(processString("a1b") == "ab");
        CHECK(processString("3c") == "c");
        CHECK(processString("x5y7z") == "xyz");
    }

    SECTION("Нечетная цифра последняя") {
        CHECK(processString("ab9") == "ab");
        CHECK(processString("7") == "");
    }

    SECTION("Несколько нечетных цифр") {
        CHECK(processString("1a3b5") == "ab");
        CHECK(processString("7c9d1") == "cd");
    }
}

TEST_CASE("Обработка смешанных строк") {
    SECTION("Четные и нечетные цифры") {
        CHECK(processString("a1b2c3d4") == "ab2++cd4");
        CHECK(processString("1a2b3c4") == "a2++bc4");
        CHECK(processString("24x6y8") == "2++4++x6++y8");
    }

    SECTION("Цифры в начале и конце") {
        CHECK(processString("1hello2world3") == "hello2++world");
        CHECK(processString("8test4") == "8++test4");
        CHECK(processString("9test7") == "test");
    }

    SECTION("Без цифр") {
        CHECK(processString("hello") == "hello");
        CHECK(processString("") == "");
        CHECK(processString("abc!@#") == "abc!@#");
    }
}