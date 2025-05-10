#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"

template <typename T>
class MySet : public MyVector<T> {
protected:
    int qFind(const T& element) const {
        int left = 0;
        int right = this->size - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (this->pdata[mid] == element) return mid;
            else if (this->pdata[mid] < element) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

public:
    MySet() : MyVector<T>(1) {}

    void add_element(const T& element) override {
        if (this->find(element) == -1) MyVector<T>::add_element(element);
    }

    void delete_element(const T& element) {
        int idx = this->find(element);
        if (idx != -1) MyVector<T>::delete_element(idx);
    }

    MySet operator+(const MySet& other) const {
        MySet result = *this;
        for (size_t i = 0; i < other.size; ++i) result.add_element(other.pdata[i]);
        return result;
    }

    MySet operator*(const MySet& other) const {
        MySet result;
        for (size_t i = 0; i < this->size; ++i)
            if (other.find(this->pdata[i]) != -1) result.add_element(this->pdata[i]);
        return result;
    }

    MySet operator-(const MySet& other) const {
        MySet result;
        for (size_t i = 0; i < this->size; ++i)
            if (other.find(this->pdata[i]) == -1) result.add_element(this->pdata[i]);
        return result;
    }

    bool operator==(const MySet& other) const {
        if (this->size != other.size) return false;
        for (size_t i = 0; i < this->size; ++i)
            if (this->pdata[i] != other.pdata[i]) return false;
        return true;
    }
};

template <>
class MySet<char*> : public MyVector<char*> {
protected:
    int qFind(const char* const& element) const {
        int left = 0;
        int right = this->size - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int cmp = strcmp(this->pdata[mid], element);
            if (cmp == 0) return mid;
            else if (cmp < 0) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

public:
    MySet() : MyVector<char*>(1) {}

    void add_element(const char* element) override {
        if (this->find(element) == -1) MyVector<char*>::add_element(element);
    }

    void delete_element(const char* const& element) {
        int idx = this->find(element);
        if (idx != -1) MyVector<char*>::delete_element(idx);
    }

    MySet operator+(const MySet& other) const {
        MySet result = *this;
        for (size_t i = 0; i < other.size; ++i) result.add_element(other.pdata[i]);
        return result;
    }

    MySet operator*(const MySet& other) const {
        MySet result;
        for (size_t i = 0; i < this->size; ++i)
            if (other.find(this->pdata[i]) != -1) result.add_element(this->pdata[i]);
        return result;
    }

    MySet operator-(const MySet& other) const {
        MySet result;
        for (size_t i = 0; i < this->size; ++i)
            if (other.find(this->pdata[i]) == -1) result.add_element(this->pdata[i]);
        return result;
    }

    bool operator==(const MySet& other) const {
        if (this->size != other.size) return false;
        for (size_t i = 0; i < this->size; ++i)
            if (strcmp(this->pdata[i], other.pdata[i]) != 0) return false;
        return true;
    }
};

template class MySet<int>;
template class MySet<double>;
template class MySet<char*>;
#endif
