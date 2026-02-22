#include "lists.h"
#include <iostream>
#include <string>
#include <cctype>

// Функция для вывода списка
template <typename ListType>
void printList(ListType& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
}

// Обработка строки: удаление лишних пробелов
template <typename ListType>
void processString(ListType& list) {
    if (list.empty()) return;

    // Удаляем пробелы в начале
    while (!list.empty() && list.front() == ' ') {
        list.pop_front();
    }

    // Удаляем пробелы в конце
    while (!list.empty() && list.back() == ' ') {
        list.pop_back();
    }

    // Удаляем лишние пробелы между словами
    auto it = list.begin();
    if (it == list.end()) return;

    auto prev = it;
    ++it;

    while (it != list.end()) {
        if (*prev == ' ' && *it == ' ') {
            it = list.begin();
            for (auto temp = list.begin(); temp != list.end(); ++temp) {
                if (temp.getNode() == it.getNode()) break;
                ++it;
            }
            list.remove(' ');
            break;
        }
        prev = it;
        ++it;
    }
}

int main() {
    int choice;
    std::cout << "Choose type of list:\n";
    std::cout << "1. One-way list\n";
    std::cout << "2. Two-way list\n";
    std::cout << "Your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::string input;
    std::cout << "Input string: ";
    std::getline(std::cin, input);

    if (choice == 1) {
        OneList<char> charList;
        for (char c : input) {
            charList.push_back(c);
        }

        std::cout << "\nInput string: ";
        printList(charList);

        processString(charList);

        std::cout << "Output string: ";
        printList(charList);

        std::cout << "\nDemonstration (One-way list):\n";
        std::cout << "Length of list: " << charList.size() << std::endl;
        if (!charList.empty()) {
            std::cout << "First element: " << charList.front() << std::endl;
            std::cout << "Last element: " << charList.back() << std::endl;
        }

        charList.push_front('>');
        charList.push_back('<');
        std::cout << "After adding '>' and '<': ";
        printList(charList);

        charList.remove(' ');
        std::cout << "After removing spaces: ";
        printList(charList);
    }
    else if (choice == 2) {
        DoubleList<char> charList;
        for (char c : input) {
            charList.push_back(c);
        }

        std::cout << "\nInput string: ";
        printList(charList);

        processString(charList);

        std::cout << "Output string: ";
        printList(charList);

        std::cout << "\nDemonstration (Two-way list):\n";
        std::cout << "Length of list: " << charList.size() << std::endl;
        if (!charList.empty()) {
            std::cout << "First element: " << charList.front() << std::endl;
            std::cout << "Last element: " << charList.back() << std::endl;
        }

        // Демонстрация сортировки
        std::cout << "\nSorting demonstration:\n";
        std::cout << "Before bubble sort: ";
        printList(charList);

        charList.bubbleSort();
        std::cout << "After bubble sort: ";
        printList(charList);

        charList.push_back('z');
        charList.push_back('a');
        charList.push_back('m');

        std::cout << "Before shell sort: ";
        printList(charList);

        charList.shellSort();
        std::cout << "After shell sort: ";
        printList(charList);
    }
    else {
        std::cout << "Wrong choice!\n";
        return 1;
    }

    return 0;
}
