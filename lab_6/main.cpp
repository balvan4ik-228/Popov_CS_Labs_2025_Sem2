#include "Term/Term.h"
#include "Polynomial/Polynomial.h"
#include <iostream>

int main() {
    // Пример работы с Term
    Term t1(3, 2);
    Term t2(-1, 2);
    Term sum = t1 + t2;
    std::cout << "Sum of terms: " << sum << std::endl;

    // Пример ввода Term
    Term t3;
    std::cout << "Enter a term (e.g., -5x^3): ";
    std::cin >> t3;
    std::cout << "You entered: " << t3 << std::endl;

    // Пример работы с Polynomial
    Polynomial p1(Term(3, 2));
    Polynomial p2(Term(-1, 2));
    Polynomial p3 = p1 + p2;
    std::cout << "Sum of polynomials: " << p3 << std::endl;

    // Пример ввода Polynomial
    Polynomial p4;
    std::cout << "Enter a polynomial (e.g., 3x^2 - x^2 +5x^5 -4x^3 +x^2 -7): ";
    std::cin.ignore(); // Очистка буфера
    std::cin >> p4;
    std::cout << "You entered: " << p4 << std::endl;

    // Пример умножения полиномов
    Polynomial p5(Term(2, 1));
    Polynomial p6(Term(3, 1));
    Polynomial p7 = p5 * p6;
    std::cout << "Product of polynomials: " << p7 << std::endl;

    return 0;
}
