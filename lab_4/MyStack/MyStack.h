#ifndef MyStack_h
#define MyStack_h

#include <iostream>

template<class INF, class FRIEND>
class ListNode
{
private:
    INF d;
    ListNode *next;
    ListNode(void) { next = nullptr; }
    ~ListNode() { next = nullptr; }
    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node *top;

    void copy(const MyStack& other);
    void clear();

public:
    MyStack(void);
    ~MyStack(void);
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);

    bool empty(void) const;
    bool push(INF n);
    bool pop(void);
    INF top_inf(void) const;

    template<class T>
    friend std::ostream& operator<<(std::ostream& os, const MyStack<T>& stack);
};

#endif
