#include "MySet.h"
#include <cstring>
#include <algorithm>
#include <iostream>

template<typename T>
int MySet<T>::q_find(const T& key) const {
    int left = 0, right = static_cast<int>(this->current_size) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (this->pdata[mid] == key) return mid;
        if (this->pdata[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

template<typename T>
void MySet<T>::add_element(const T& element) {
    if (q_find(element) != -1) return;
    MyVector<T>::add_element(element);
    std::sort(this->pdata, this->pdata + this->current_size);
}

template<typename T>
void MySet<T>::delete_element(const T& element) {
    int idx = q_find(element);
    if (idx != -1)
        MyVector<T>::delete_element(static_cast<size_t>(idx));
}

template<typename T>
bool MySet<T>::is_element(const T& element) const {
    return q_find(element) != -1;
}

template<typename T>
MySet<T> MySet<T>::operator+(const MySet& other) const {
    MySet<T> result;
    size_t i = 0, j = 0;
    while (i < this->current_size && j < other.current_size) {
        if (this->pdata[i] < other.pdata[j])
            result.add_element(this->pdata[i++]);
        else if (this->pdata[i] > other.pdata[j])
            result.add_element(other.pdata[j++]);
        else {
            result.add_element(this->pdata[i]);
            ++i; ++j;
        }
    }
    while (i < this->current_size) result.add_element(this->pdata[i++]);
    while (j < other.current_size) result.add_element(other.pdata[j++]);
    return result;
}

template<typename T>
MySet<T> MySet<T>::operator*(const MySet& other) const {
    MySet<T> result;
    size_t min_size = (this->current_size < other.current_size) ? this->current_size : other.current_size;
    for (size_t i = 0; i < min_size; ++i) {
        result.add_element(this->pdata[i] * other.pdata[i]);
    }
    return result;
}

template<typename T>
MySet<T> MySet<T>::operator-(const MySet& other) const {
    MySet<T> result;
    size_t i = 0, j = 0;
    while (i < this->current_size) {
        if (j >= other.current_size || this->pdata[i] < other.pdata[j])
            result.add_element(this->pdata[i++]);
        else if (this->pdata[i] > other.pdata[j])
            ++j;
        else {
            ++i; ++j;
        }
    }
    return result;
}

template<typename T>
MySet<T>& MySet<T>::operator+=(const MySet& other) {
    *this = *this + other;
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::operator*=(const MySet& other) {
    *this = *this * other;
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::operator-=(const MySet& other) {
    *this = *this - other;
    return *this;
}

template<typename T>
bool MySet<T>::operator==(const MySet& other) const {
    if (this->current_size != other.current_size) return false;
    for (size_t i = 0; i < this->current_size; ++i)
        if (!(this->pdata[i] == other.pdata[i])) return false;
    return true;
}

// --- Специализации для char* ---

template<>
int MySet<char*>::q_find(char* const& key) const {
    int left = 0, right = static_cast<int>(this->current_size) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(this->pdata[mid], key);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

template<>
void MySet<char*>::add_element(char* const& element) {
    if (q_find(element) != -1) return;
    MyVector<char*>::add_element(element);
    std::sort(this->pdata, this->pdata + this->current_size,
        [](const char* a, const char* b) { return strcmp(a, b) < 0; });
}

template<>
void MySet<char*>::delete_element(char* const& element) {
    int idx = q_find(element);
    if (idx != -1) {
        free(this->pdata[idx]);
        MyVector<char*>::delete_element(static_cast<size_t>(idx));
    }
}

template<>
bool MySet<char*>::operator==(const MySet<char*>& other) const {
    if (this->current_size != other.current_size) return false;
    for (size_t i = 0; i < this->current_size; ++i)
        if (strcmp(this->pdata[i], other.pdata[i]) != 0) return false;
    return true;
}

template<>
MySet<char*> MySet<char*>::operator+(const MySet<char*>& other) const {
    MySet<char*> result;
    size_t i = 0, j = 0;
    while (i < this->current_size && j < other.current_size) {
        int cmp = strcmp(this->pdata[i], other.pdata[j]);
        if (cmp < 0)
            result.add_element(strdup(this->pdata[i++])); // Копия строки!
        else if (cmp > 0)
            result.add_element(strdup(other.pdata[j++])); // Копия строки!
        else {
            result.add_element(strdup(this->pdata[i]));
            ++i; ++j;
        }
    }
    while (i < this->current_size) result.add_element(strdup(this->pdata[i++]));
    while (j < other.current_size) result.add_element(strdup(other.pdata[j++]));
    return result;
}

template<>
MySet<char*> MySet<char*>::operator*(const MySet<char*>& other) const {
    MySet<char*> result;
    size_t i = 0, j = 0;
    while (i < this->current_size && j < other.current_size) {
        int cmp = strcmp(this->pdata[i], other.pdata[j]);
        if (cmp < 0) ++i;
        else if (cmp > 0) ++j;
        else {
            result.add_element(strdup(this->pdata[i]));
            ++i; ++j;
        }
    }
    return result;
}

template<>
MySet<char*> MySet<char*>::operator-(const MySet<char*>& other) const {
    MySet<char*> result;
    size_t i = 0, j = 0;
    while (i < this->current_size) {
        if (j >= other.current_size || strcmp(this->pdata[i], other.pdata[j]) < 0)
            result.add_element(strdup(this->pdata[i++]));
        else if (strcmp(this->pdata[i], other.pdata[j]) > 0)
            ++j;
        else {
            ++i; ++j;
        }
    }
    return result;
}

template class MySet<int>;
template class MySet<char*>;
