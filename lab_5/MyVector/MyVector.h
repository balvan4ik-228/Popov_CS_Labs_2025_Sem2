#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <cstring>
#include <stdexcept>

template <typename T>
struct CompareTraits {
    static bool equals(const T& a, const T& b) { return a == b; }
    static bool less(const T& a, const T& b) { return a < b; }
};

template <>
struct CompareTraits<char*> {
    static bool equals(const char* a, const char* b) { return strcmp(a, b) == 0; }
    static bool less(const char* a, const char* b) { return strcmp(a, b) < 0; }
};

template <typename T>
class MyVector {
protected:
    size_t max_size;
    size_t size;
    T* pdata;

    void resize(size_t new_max_size) {
        T* new_pdata = new T[new_max_size];
        for (size_t i = 0; i < size; ++i) new_pdata[i] = pdata[i];
        delete[] pdata;
        pdata = new_pdata;
        max_size = new_max_size;
    }

    void bubbleSort() {
        for (size_t i = 0; i < size-1; ++i)
            for (size_t j = 0; j < size-i-1; ++j)
                if (CompareTraits<T>::less(pdata[j+1], pdata[j]))
                    std::swap(pdata[j], pdata[j+1]);
    }

public:
    MyVector(size_t initial_size = 1) : max_size(initial_size), size(0), pdata(new T[max_size]) {}

    MyVector(const MyVector& other) : max_size(other.max_size), size(other.size), pdata(new T[max_size]) {
        for (size_t i = 0; i < size; ++i) pdata[i] = other.pdata[i];
    }

    virtual ~MyVector() { delete[] pdata; }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] pdata;
            max_size = other.max_size;
            size = other.size;
            pdata = new T[max_size];
            for (size_t i = 0; i < size; ++i) pdata[i] = other.pdata[i];
        }
        return *this;
    }

    virtual void add_element(const T& element) {
        if (size >= max_size) resize(max_size * 2);
        pdata[size++] = element;
        bubbleSort();
    }

    virtual void delete_element(size_t index) {
        if (index >= size) return;
        for (size_t i = index; i < size-1; ++i) pdata[i] = pdata[i+1];
        size--;
        if (size < max_size/4 && max_size > 1) resize(max_size/2);
    }

    int find(const T& element) const {
        for (size_t i = 0; i < size; ++i)
            if (CompareTraits<T>::equals(pdata[i], element)) return i;
        return -1;
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec) {
        os << "{";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.pdata[i];
            if (i != vec.size-1) os << ", ";
        }
        os << "}";
        return os;
    }
};

template <>
class MyVector<char*> {
protected:
    size_t max_size;
    size_t size;
    char** pdata;

    void resize(size_t new_max_size) {
        char** new_pdata = new char*[new_max_size];
        for (size_t i = 0; i < size; ++i) {
            new_pdata[i] = new char[strlen(pdata[i])+1];
            strcpy(new_pdata[i], pdata[i]);
            delete[] pdata[i];
        }
        delete[] pdata;
        pdata = new_pdata;
        max_size = new_max_size;
    }

    void bubbleSort() {
        for (size_t i = 0; i < size-1; ++i)
            for (size_t j = 0; j < size-i-1; ++j)
                if (strcmp(pdata[j], pdata[j+1]) > 0)
                    std::swap(pdata[j], pdata[j+1]);
    }

public:
    MyVector(size_t initial_size = 1) : max_size(initial_size), size(0), pdata(new char*[max_size]) {}

    MyVector(const MyVector& other) : max_size(other.max_size), size(other.size), pdata(new char*[max_size]) {
        for (size_t i = 0; i < size; ++i) {
            pdata[i] = new char[strlen(other.pdata[i])+1];
            strcpy(pdata[i], other.pdata[i]);
        }
    }

    virtual ~MyVector() {
        for (size_t i = 0; i < size; ++i) delete[] pdata[i];
        delete[] pdata;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) delete[] pdata[i];
            delete[] pdata;
            max_size = other.max_size;
            size = other.size;
            pdata = new char*[max_size];
            for (size_t i = 0; i < size; ++i) {
                pdata[i] = new char[strlen(other.pdata[i])+1];
                strcpy(pdata[i], other.pdata[i]);
            }
        }
        return *this;
    }

    virtual void add_element(const char* element) {
        if (size >= max_size) resize(max_size*2);
        pdata[size] = new char[strlen(element)+1];
        strcpy(pdata[size], element);
        size++;
        bubbleSort();
    }

    virtual void delete_element(size_t index) {
        if (index >= size) return;
        delete[] pdata[index];
        for (size_t i = index; i < size-1; ++i) pdata[i] = pdata[i+1];
        size--;
        if (size < max_size/4 && max_size > 1) resize(max_size/2);
    }

    int find(const char* element) const {
        for (size_t i = 0; i < size; ++i)
            if (strcmp(pdata[i], element) == 0) return i;
        return -1;
    }

    char*& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const char* operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec) {
        os << "{";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.pdata[i];
            if (i != vec.size-1) os << ", ";
        }
        os << "}";
        return os;
    }
};

template class MyVector<int>;
template class MyVector<double>;
template class MyVector<char*>;

#endif // MYVECTOR_H
