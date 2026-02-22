#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void prog1() {
    char ch;
    char* str = nullptr;
    int size = 0;

    cout << "Input string:" << endl;

    while (cin.get(ch) && ch != '\n') {
        char* newStr = (char*)malloc((size + 2) * sizeof(char));

        for (int i = 0; i < size; i++) {
            newStr[i] = str[i];
        }

        newStr[size] = ch;
        newStr[size + 1] = '\0';

        if (str) free(str);
        str = newStr;
        size++;
    }

    if (str == nullptr) {
        cout << "String empty." << endl;
        return;
    }

    cout << "Original string: " << str << endl;

    // Обработка строки: после каждой четной цифры (не последней) добавить "++", нечетные цифры удалить
    char* result = nullptr;
    int resultSize = 0;

    for (int i = 0; i < size; i++) {
        char currentChar = str[i];

        // Проверяем, является ли символ цифрой
        if (currentChar >= '0' && currentChar <= '9') {
            int digit = currentChar - '0';

            if (digit % 2 == 0) {
                // Четная цифра
                if (i < size - 1) {
                    // Не последний символ - добавляем цифру и "++"
                    char* newResult = (char*)malloc((resultSize + 3) * sizeof(char));
                    for (int j = 0; j < resultSize; j++) {
                        newResult[j] = result[j];
                    }
                    newResult[resultSize] = currentChar;
                    newResult[resultSize + 1] = '+';
                    newResult[resultSize + 2] = '+';
                    newResult[resultSize + 3] = '\0';

                    if (result) free(result);
                    result = newResult;
                    resultSize += 3;
                }
                else {
                    // Последний символ - просто добавляем цифру
                    char* newResult = (char*)malloc((resultSize + 2) * sizeof(char));
                    for (int j = 0; j < resultSize; j++) {
                        newResult[j] = result[j];
                    }
                    newResult[resultSize] = currentChar;
                    newResult[resultSize + 1] = '\0';

                    if (result) free(result);
                    result = newResult;
                    resultSize += 1;
                }
            } // Нечетные цифры просто пропускаем (удаляем)
        }
        else {
            // Не цифра - просто копируем
            char* newResult = (char*)malloc((resultSize + 2) * sizeof(char));
            for (int j = 0; j < resultSize; j++) {
                newResult[j] = result[j];
            }
            newResult[resultSize] = currentChar;
            newResult[resultSize + 1] = '\0';

            if (result) free(result);
            result = newResult;
            resultSize++;
        }
    }

    if (result) {
        cout << "Processed string: " << result << endl;
        free(result);
    }
    else {
        cout << "Result is empty." << endl;
    }

    free(str);
}