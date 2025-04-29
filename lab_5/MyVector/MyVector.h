#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>

template<typename T>
class MyVector {
protected:
    size_t max_size;
    size_t current_size;
    T* pdata;

    void resize(size_t new_max_size);

public:
    MyVector(size_t initial_size = 8);
    MyVector(const MyVector& other);
    virtual ~MyVector();

    virtual void add_element(const T& element);
    virtual void delete_element(size_t index);

    int find(const T& key) const;
    size_t size() const { return current_size; }
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    MyVector& operator=(const MyVector& other);
    MyVector& operator*(const MyVector& other);
};

#endif
