#include "MyVector.h"
#include <stdexcept>

template<typename T>
MyVector<T>::MyVector(size_t initial_size)
    : max_size(initial_size), current_size(0), pdata(new T[initial_size]) {}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : max_size(other.max_size), current_size(other.current_size), pdata(new T[other.max_size]) {
    std::copy(other.pdata, other.pdata + other.current_size, pdata);
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] pdata;
}

template<typename T>
void MyVector<T>::resize(size_t new_max_size) {
    T* new_data = new T[new_max_size];
    std::copy(pdata, pdata + current_size, new_data);
    delete[] pdata;
    pdata = new_data;
    max_size = new_max_size;
}

template<typename T>
void MyVector<T>::add_element(const T& element) {
    if (current_size >= max_size)
        resize(max_size * 2);
    pdata[current_size++] = element;
}

template<typename T>
void MyVector<T>::delete_element(size_t index) {
    if (index >= current_size) return;
    for (size_t i = index; i < current_size - 1; ++i)
        pdata[i] = pdata[i + 1];
    --current_size;
    if (current_size < max_size / 4 && max_size > 8)
        resize(max_size / 2);
}

template<typename T>
int MyVector<T>::find(const T& key) const {
    for (size_t i = 0; i < current_size; ++i)
        if (pdata[i] == key) return static_cast<int>(i);
    return -1;
}

template<typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= current_size) throw std::out_of_range("Index out of range");
    return pdata[index];
}

template<typename T>
const T& MyVector<T>::operator[](size_t index) const {
    if (index >= current_size) throw std::out_of_range("Index out of range");
    return pdata[index];
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this == &other) return *this;
    delete[] pdata;
    max_size = other.max_size;
    current_size = other.current_size;
    pdata = new T[max_size];
    std::copy(other.pdata, other.pdata + current_size, pdata);
    return *this;
}

template class MyVector<int>;
template class MyVector<char*>;
