#define _CRT_SECURE_NO_WARNINGS
#include "method_c.h"
#include <ctype.h>
#include <string.h>

void process_cstring(char* str) {
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
            // нечетные цифры пропускаем
        }
        else {
            result[pos++] = str[i];
        }
    }
    result[pos] = '\0';
    strcpy(str, result);
}