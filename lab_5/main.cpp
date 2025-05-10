#include <iostream>
#include "MySet/MySet.h"

int main() {
    MySet<int> A;
    A.add_element(10);
    A.add_element(20);
    A.add_element(30);

    MySet<int> B;
    B.add_element(20);
    B.add_element(40);
    B.add_element(50);

    std::cout << "Множество A: " << A << std::endl;
    std::cout << "Множество B: " << B << std::endl;
    std::cout << "Объединение (A + B): " << A + B << std::endl;
    std::cout << "Пересечение (A * B): " << A * B << std::endl;
    std::cout << "Разность (A - B): " << A - B << std::endl;

    MySet<char*> C;
    C.add_element("яблоко");
    C.add_element("банан");
    C.add_element("апельсин");

    MySet<char*> D;
    D.add_element("банан");
    D.add_element("виноград");
    D.add_element("апельсин");

    std::cout << "\nМножество C: " << C << std::endl;
    std::cout << "Множество D: " << D << std::endl;
    std::cout << "Объединение (C + D): " << C + D << std::endl;
    std::cout << "Пересечение (C * D): " << C * D << std::endl;
    std::cout << "Разность (C - D): " << C - D << std::endl;

    return 0;
}
