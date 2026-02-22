#define _CRT_SECURE_NO_WARNINGS
#include "array.h"
#include <string.h>
#include <ctype.h>

void process_string(char* str) {
    if (str == NULL) return;

    char result[256] = "";
    int pos = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            int digit = str[i] - '0';
            if (digit % 2 == 0) { // четная цифра
                result[pos++] = str[i];
                if (i < len - 1) { // если не последний символ
                    result[pos++] = '+';
                    result[pos++] = '+';
                }
            }
            // нечетные цифры просто пропускаем (не добавляем в результат)
        }
        else {
            result[pos++] = str[i];
        }
    }
    result[pos] = '\0';
    strcpy(str, result);
}