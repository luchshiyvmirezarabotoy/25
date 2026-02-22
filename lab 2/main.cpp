#include <iostream>
#include "prog1.h"
#include "prog2.h"
#include "prog3.h"
using namespace std;

int main() {
    int choice;

    cout << "Choose prog:" << endl;
    cout << "1. output malloc/free" << endl;
    cout << "2. output calloc/realloc/free" << endl;
    cout << "3. file work" << endl;
    cout << "your choise: ";
    cin >> choice;
    cin.ignore(); // очистка буфера

    switch (choice) {
    case 1:
        prog1();
        break;
    case 2:
        prog2();
        break;
    case 3:
        prog3();
        break;
    default:
        cout << "Неверный выбор." << endl;
    }

    return 0;
}