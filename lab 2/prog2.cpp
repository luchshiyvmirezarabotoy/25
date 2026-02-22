#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void prog2() {
    char ch;
    char* str = nullptr;
    int capacity = 5;
    int size = 0;

    str = (char*)calloc(capacity, sizeof(char));

    cout << "Input string:" << endl;

    while (cin.get(ch) && ch != '\n') {
        if (size == capacity - 1) {
            capacity += 5;
            str = (char*)realloc(str, capacity * sizeof(char));
        }
        str[size] = ch;
        size++;
    }
    str[size] = '\0';

    if (size == 0) {
        cout << "Empty string." << endl;
        free(str);
        return;
    }

    cout << "Original string: " << str << endl;

    // Обработка строки: после каждой четной цифры (не последней) добавить "++", нечетные цифры удалить
    char* result = nullptr;
    int resultCapacity = 5;
    int resultSize = 0;

    result = (char*)calloc(resultCapacity, sizeof(char));

    for (int i = 0; i < size; i++) {
        char currentChar = str[i];

        // Проверяем, является ли символ цифрой
        if (currentChar >= '0' && currentChar <= '9') {
            int digit = currentChar - '0';

            if (digit % 2 == 0) {
                // Четная цифра
                if (i < size - 1) {
                    // Не последний символ - добавляем цифру и "++"
                    // Убедимся, что хватит места (цифра + два плюса)
                    while (resultSize + 3 >= resultCapacity) {
                        resultCapacity += 5;
                        result = (char*)realloc(result, resultCapacity * sizeof(char));
                    }
                    result[resultSize++] = currentChar;
                    result[resultSize++] = '+';
                    result[resultSize++] = '+';
                }
                else {
                    // Последний символ - просто добавляем цифру
                    while (resultSize + 1 >= resultCapacity) {
                        resultCapacity += 5;
                        result = (char*)realloc(result, resultCapacity * sizeof(char));
                    }
                    result[resultSize++] = currentChar;
                }
            } // Нечетные цифры просто пропускаем (удаляем)
        }
        else {
            // Не цифра - просто копируем
            while (resultSize + 1 >= resultCapacity) {
                resultCapacity += 5;
                result = (char*)realloc(result, resultCapacity * sizeof(char));
            }
            result[resultSize++] = currentChar;
        }
    }
    result[resultSize] = '\0';

    if (resultSize > 0) {
        cout << "Processed string: " << result << endl;
    }
    else {
        cout << "Result is empty." << endl;
    }

    free(result);
    free(str);
}
