#include "Polynomial/Polynomial.h"
#include <iostream>
#include <sstream>
#include <cstring>

int main() {
    Term t1(3, 2);
    Term t2(-1, 2);
    Term t3 = t1 + t2;

    std::cout << "Term 1: " << t1 << std::endl;
    std::cout << "Term 2: " << t2 << std::endl;
    std::cout << "Term 1 + Term 2: " << t3 << std::endl;

    std::cout << "Введите полином 1: " << std::endl;
    Polynomial p1;
    std::cin >> p1;
    std::cout << "Полином 1: " << std::endl << p1 << std::endl;

    std::cout << "Введите полином 2: " << std::endl;
    Polynomial p2;
    std::cin >> p2;
    std::cout << "Полином 2: " << std::endl << p2 << std::endl;

    Polynomial p3 = p1 + p2;
    std::cout << "p3 = p1 + p2 = " << p3 << std::endl;

    Polynomial p4 = p1 * p2;
    std::cout << "p4 = p1 * p2 = " << p4 << std::endl;

    Polynomial p5 = p1 - p2;
    std::cout << "p5 = p1 - p2 = " << p5 << std::endl;

    return 0;
}
