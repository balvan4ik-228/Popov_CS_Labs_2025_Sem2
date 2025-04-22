#include "MyStack/MyStack.h"
#include <iostream>

void Multipliers(int n, MyStack<int> &stack) {
    if (n < 2) {
        stack.push(n);
        return;
    }

    int divisor = 2;
    while (n > 1) {
        while (n % divisor == 0) {
            stack.push(divisor);
            n /= divisor;
        }
        divisor++;
    }
}

int main() {
    int N = 3960;
    MyStack<int> stack;

    Multipliers(N, stack);

    std::cout << N << " = ";
    MyStack<int> temp = stack;
    bool first = true;
    while (!temp.empty()) {
        if (!first) {
            std::cout << " * ";
        }
        std::cout << temp.top_inf();
        temp.pop();
        first = false;
    }
    std::cout << std::endl;

    std::cout << N << " = " << stack << std::endl;

    return 0;
}
