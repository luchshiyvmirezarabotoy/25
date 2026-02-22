#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include "catch.hpp"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>

#include "array.h"
#include "method_c.h"
#include "method_fille.h"

using namespace std;

string read_file() {
    char res[256] = "";
    FILE* in = fopen("Laba1/output.txt", "r");
    if (in && fgets(res, 256, in) != NULL) {
        fclose(in);
    }
    return string(res);
}

void write_file(const char str[]) {
    _mkdir("Laba1");
    FILE* out = fopen("Laba1/input.txt", "w");
    if (!out) return;
    fputs(str, out);
    fclose(out);
}

TEST_CASE("Array: Empty string", "[array_string]") {
    char str[256] = "";
    process_string(str);
    REQUIRE(strcmp(str, "") == 0);
}

TEST_CASE("Array: No digits", "[array_string]") {
    char str[256] = "Hello World";
    process_string(str);
    REQUIRE(strcmp(str, "Hello World") == 0);
}

TEST_CASE("Array: Single even digit not last", "[array_string]") {
    char str[256] = "a2b";
    process_string(str);
    REQUIRE(strcmp(str, "a2++b") == 0);
}

TEST_CASE("Array: Single even digit as last", "[array_string]") {
    char str[256] = "ab2";
    process_string(str);
    REQUIRE(strcmp(str, "ab2") == 0);
}

TEST_CASE("Array: Single odd digit", "[array_string]") {
    char str[256] = "a3b";
    process_string(str);
    REQUIRE(strcmp(str, "ab") == 0);
}

TEST_CASE("Array: Multiple even digits", "[array_string]") {
    char str[256] = "a2b4c6d";
    process_string(str);
    REQUIRE(strcmp(str, "a2++b4++c6++d") == 0);
}

TEST_CASE("Array: Multiple odd digits", "[array_string]") {
    char str[256] = "a1b3c5d";
    process_string(str);
    REQUIRE(strcmp(str, "abcd") == 0);
}

TEST_CASE("Array: Mixed digits", "[array_string]") {
    char str[256] = "a2b3c4d5e6f";
    process_string(str);
    REQUIRE(strcmp(str, "a2++bc4++de6++f") == 0);
}

TEST_CASE("Array: Even digit at the end", "[array_string]") {
    char str[256] = "a2b4c6";
    process_string(str);
    REQUIRE(strcmp(str, "a2++b4++c6") == 0);
}

TEST_CASE("Array: Consecutive digits", "[array_string]") {
    char str[256] = "a24b";
    process_string(str);
    REQUIRE(strcmp(str, "a2++4++b") == 0);
}

TEST_CASE("Array: Digit 0 as even", "[array_string]") {
    char str[256] = "a0b";
    process_string(str);
    REQUIRE(strcmp(str, "a0++b") == 0);
}

TEST_CASE("C String: Empty string", "[c_string]") {
    char str[256] = "";
    process_cstring(str);
    REQUIRE(strcmp(str, "") == 0);
}

TEST_CASE("C String: No digits", "[c_string]") {
    char str[256] = "Hello World";
    process_cstring(str);
    REQUIRE(strcmp(str, "Hello World") == 0);
}

TEST_CASE("C String: Single even digit not last", "[c_string]") {
    char str[256] = "a2b";
    process_cstring(str);
    REQUIRE(strcmp(str, "a2++b") == 0);
}

TEST_CASE("C String: Single even digit as last", "[c_string]") {
    char str[256] = "ab2";
    process_cstring(str);
    REQUIRE(strcmp(str, "ab2") == 0);
}

TEST_CASE("C String: Single odd digit", "[c_string]") {
    char str[256] = "a3b";
    process_cstring(str);
    REQUIRE(strcmp(str, "ab") == 0);
}

TEST_CASE("C String: Multiple even digits", "[c_string]") {
    char str[256] = "a2b4c6d";
    process_cstring(str);
    REQUIRE(strcmp(str, "a2++b4++c6++d") == 0);
}

TEST_CASE("C String: Multiple odd digits", "[c_string]") {
    char str[256] = "a1b3c5d";
    process_cstring(str);
    REQUIRE(strcmp(str, "abcd") == 0);
}

TEST_CASE("C String: Mixed digits", "[c_string]") {
    char str[256] = "a2b3c4d5e6f";
    process_cstring(str);
    REQUIRE(strcmp(str, "a2++bc4++de6++f") == 0);
}

TEST_CASE("C String: Even digit at the end", "[c_string]") {
    char str[256] = "a2b4c6";
    process_cstring(str);
    REQUIRE(strcmp(str, "a2++b4++c6") == 0);
}

TEST_CASE("C String: Consecutive digits", "[c_string]") {
    char str[256] = "a24b";
    process_cstring(str);
    REQUIRE(strcmp(str, "a2++4++b") == 0);
}

TEST_CASE("C String: Digit 0 as even", "[c_string]") {
    char str[256] = "a0b";
    process_cstring(str);
    REQUIRE(strcmp(str, "a0++b") == 0);
}

TEST_CASE("File: Empty file", "[file_string]") {
    write_file("");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "");
}

TEST_CASE("File: No digits", "[file_string]") {
    write_file("Hello World");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "Hello World");
}

TEST_CASE("File: Single even digit not last", "[file_string]") {
    write_file("a2b");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a2++b");
}

TEST_CASE("File: Single even digit as last", "[file_string]") {
    write_file("ab2");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "ab2");
}

TEST_CASE("File: Single odd digit", "[file_string]") {
    write_file("a3b");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "ab");
}

TEST_CASE("File: Multiple even digits", "[file_string]") {
    write_file("a2b4c6d");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a2++b4++c6++d");
}

TEST_CASE("File: Multiple odd digits", "[file_string]") {
    write_file("a1b3c5d");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "abcd");
}

TEST_CASE("File: Mixed digits", "[file_string]") {
    write_file("a2b3c4d5e6f");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a2++bc4++de6++f");
}

TEST_CASE("File: Even digit at the end", "[file_string]") {
    write_file("a2b4c6");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a2++b4++c6");
}

TEST_CASE("File: Consecutive digits", "[file_string]") {
    write_file("a24b");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a2++4++b");
}

TEST_CASE("File: Digit 0 as even", "[file_string]") {
    write_file("a0b");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "a0++b");
}