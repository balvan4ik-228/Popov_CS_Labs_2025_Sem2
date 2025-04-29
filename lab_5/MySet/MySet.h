#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"

template<typename T>
class MySet : public MyVector<T> {
protected:
    int q_find(const T& key) const;

public:
    using MyVector<T>::MyVector;

    virtual void add_element(const T& element) override;
    virtual void delete_element(const T& element);
    bool is_element(const T& element) const;

    MySet operator+(const MySet& other) const;
    MySet operator*(const MySet& other) const;
    MySet operator-(const MySet& other) const;
    MySet& operator+=(const MySet& other);
    MySet& operator*=(const MySet& other);
    MySet& operator-=(const MySet& other);
    bool operator==(const MySet& other) const;
};

#endif
