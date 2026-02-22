#ifndef LISTS_HPP
#define LISTS_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>

// Базовый класс элемента списка
template <typename T>
class Element {
public:
    T data;
    Element(T value) : data(value) {}
    virtual ~Element() {}
};

// Узел односвязного списка
template <typename T>
class OneListNode : public Element<T> {
public:
    OneListNode<T>* next;
    OneListNode(T value) : Element<T>(value), next(nullptr) {}
};

// Узел двусвязного списка
template <typename T>
class DoubleListNode : public Element<T> {
public:
    DoubleListNode<T>* next;
    DoubleListNode<T>* prev;
    DoubleListNode(T value) : Element<T>(value), next(nullptr), prev(nullptr) {}
};

// Итератор для односвязного списка
template <typename T>
class OneListIterator {
private:
    OneListNode<T>* current;
public:
    OneListIterator(OneListNode<T>* node = nullptr) : current(node) {}

    T& operator*() {
        if (!current) throw std::runtime_error("Dereferencing end iterator");
        return current->data;
    }

    OneListIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    OneListIterator operator++(int) {
        OneListIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const OneListIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const OneListIterator& other) const {
        return current != other.current;
    }

    OneListNode<T>* getNode() const { return current; }
};

// Итератор для двусвязного списка
template <typename T>
class DoubleListIterator {
private:
    DoubleListNode<T>* current;
public:
    DoubleListIterator(DoubleListNode<T>* node = nullptr) : current(node) {}

    T& operator*() {
        if (!current) throw std::runtime_error("Dereferencing end iterator");
        return current->data;
    }

    DoubleListIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    DoubleListIterator operator++(int) {
        DoubleListIterator temp = *this;
        ++(*this);
        return temp;
    }

    DoubleListIterator& operator--() {
        if (current) current = current->prev;
        return *this;
    }

    DoubleListIterator operator--(int) {
        DoubleListIterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const DoubleListIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const DoubleListIterator& other) const {
        return current != other.current;
    }

    DoubleListNode<T>* getNode() const { return current; }
};

// Односвязный список
template <typename T>
class OneList {
private:
    OneListNode<T>* head;
    OneListNode<T>* tail;
    size_t listSize;

public:
    using Iterator = OneListIterator<T>;

    OneList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~OneList() { clear(); }

    void push_front(T value) {
        OneListNode<T>* newNode = new OneListNode<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }

    void push_back(T value) {
        OneListNode<T>* newNode = new OneListNode<T>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    void pop_front() {
        if (!head) return;
        OneListNode<T>* temp = head;
        head = head->next;
        delete temp;
        listSize--;
        if (!head) tail = nullptr;
    }

    void pop_back() {
        if (!tail) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            OneListNode<T>* current = head;
            while (current->next != tail) current = current->next;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        listSize--;
    }

    void remove(T value) {
        OneListNode<T>* current = head;
        OneListNode<T>* prev = nullptr;
        while (current) {
            if (current->data == value) {
                OneListNode<T>* temp = current;
                if (prev) prev->next = current->next;
                else head = current->next;
                if (current == tail) tail = prev;
                current = current->next;
                delete temp;
                listSize--;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }

    size_t size() const { return listSize; }

    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    bool empty() const { return listSize == 0; }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void clear() {
        while (!empty()) pop_front();
    }
};

// Двусвязный список
template <typename T>
class DoubleList {
private:
    DoubleListNode<T>* head;
    DoubleListNode<T>* tail;
    size_t listSize;

public:
    using Iterator = DoubleListIterator<T>;

    DoubleList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~DoubleList() { clear(); }

    void push_front(T value) {
        DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void push_back(T value) {
        DoubleListNode<T>* newNode = new DoubleListNode<T>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    void pop_front() {
        if (!head) return;
        DoubleListNode<T>* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        listSize--;
    }

    void pop_back() {
        if (!tail) return;
        DoubleListNode<T>* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        listSize--;
    }

    void remove(T value) {
        DoubleListNode<T>* current = head;
        while (current) {
            if (current->data == value) {
                DoubleListNode<T>* temp = current;
                if (current->prev) current->prev->next = current->next;
                else head = current->next;
                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;
                current = current->next;
                delete temp;
                listSize--;
            }
            else {
                current = current->next;
            }
        }
    }

    size_t size() const { return listSize; }

    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    bool empty() const { return listSize == 0; }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void clear() {
        while (!empty()) pop_front();
    }

    // Сортировка пузырьком
    void bubbleSort() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            DoubleListNode<T>* current = head;
            while (current->next) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // Сортировка Шелла
    void shellSort() {
        if (!head || !head->next) return;

        // Преобразуем список в массив
        T* arr = new T[listSize];
        DoubleListNode<T>* current = head;
        for (size_t i = 0; i < listSize; ++i) {
            arr[i] = current->data;
            current = current->next;
        }

        // Сортировка Шелла
        for (size_t gap = listSize / 2; gap > 0; gap /= 2) {
            for (size_t i = gap; i < listSize; ++i) {
                T temp = arr[i];
                size_t j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }

        // Возвращаем отсортированные данные обратно в список
        current = head;
        for (size_t i = 0; i < listSize; ++i) {
            current->data = arr[i];
            current = current->next;
        }

        delete[] arr;
    }
};

#endif // LISTS_HPP
