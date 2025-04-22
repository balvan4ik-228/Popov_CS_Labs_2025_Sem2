#include "MyStack.h"

template<class INF>
void MyStack<INF>::copy(const MyStack& other) {
    if (other.top == nullptr) {
        top = nullptr;
        return;
    }

    top = new Node;
    top->d = other.top->d;

    Node* current = top;
    Node* otherCurrent = other.top->next;

    while (otherCurrent != nullptr) {
        current->next = new Node;
        current = current->next;
        current->d = otherCurrent->d;
        otherCurrent = otherCurrent->next;
    }
    current->next = nullptr;
}

template<class INF>
void MyStack<INF>::clear() {
    while (!empty()) {
        pop();
    }
}

template<class INF>
MyStack<INF>::MyStack(void) : top(nullptr) {}

template<class INF>
MyStack<INF>::~MyStack(void) {
    clear();
}

template<class INF>
MyStack<INF>::MyStack(const MyStack& other) : top(nullptr) {
    copy(other);
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

template<class INF>
bool MyStack<INF>::empty(void) const {
    return top == nullptr;
}

template<class INF>
bool MyStack<INF>::push(INF n) {
    Node *newNode = new Node;
    newNode->d = n;
    newNode->next = top;
    top = newNode;
    return true;
}

template<class INF>
bool MyStack<INF>::pop(void) {
    if (empty()) return false;

    Node *temp = top;
    top = top->next;
    temp->next = nullptr;
    delete temp;
    return true;
}

template<class INF>
INF MyStack<INF>::top_inf(void) const {
    if (!empty()) {
        return top->d;
    }
    throw "Стек пуст!";
}

template<class INF>
std::ostream& operator<<(std::ostream& os, const MyStack<INF>& stack) {
    MyStack<INF> temp = stack;
    MyStack<INF> tempReverse;

    while (!temp.empty()) {
        tempReverse.push(temp.top_inf());
        temp.pop();
    }

    bool first = true;
    while (!tempReverse.empty()) {
        if (!first) {
            os << " * ";
        }
        os << tempReverse.top_inf();
        tempReverse.pop();
        first = false;
    }
    return os;
}

template class MyStack<int>;
template std::ostream& operator<<(std::ostream& os, const MyStack<int>& stack);
