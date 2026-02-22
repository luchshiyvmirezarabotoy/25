#define _CRT_SECURE_NO_WARNINGS
#include "method_fille.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void process_file_string() {
    FILE* in = fopen("Laba1/input.txt", "r");
    if (!in) return;

    char str[256] = "";
    // Проверяем, удалось ли что-то прочитать
    if (fgets(str, 256, in) == NULL) {
        fclose(in);
        // Если файл пустой, создаем пустой выходной файл
        FILE* out = fopen("Laba1/output.txt", "w");
        if (out) {
            fputs("", out);
            fclose(out);
        }
        return;
    }
    fclose(in);

    // Убираем возможный символ новой строки
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--; // обновляем длину после удаления \n
    }

    // Если строка пустая после удаления \n
    if (len == 0) {
        FILE* out = fopen("Laba1/output.txt", "w");
        if (out) {
            fputs("", out);
            fclose(out);
        }
        return;
    }

    char result[256] = "";
    int pos = 0;

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

    FILE* out = fopen("Laba1/output.txt", "w");
    if (!out) return;
    fputs(result, out);
    fclose(out);
}