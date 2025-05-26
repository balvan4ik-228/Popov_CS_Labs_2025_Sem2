#include "Term/Term.h"
#include "Polynomial/Polynomial.h"
#include <iostream>

int main() {
    // Ввод термов
    Term t1, t2;
    std::cout << "Введите первый терм (пример: -5x^3): ";
    std::cin >> t1;
    std::cout << "Введите второй терм: ";
    std::cin >> t2;

    // Сложение термов
    try {
        Term sum = t1 + t2;
        std::cout << "Сумма термов: " << sum << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    // Ввод полиномов
    Polynomial p1, p2;
    std::cout << "\nВведите первый полином (пример: 3x^0 - 4x^1 + 1x^4 - 8 + 3x^2 + 5x^2): ";
    std::cin.ignore(); // Очистка буфера
    std::cin >> p1;
    std::cout << "Нормализованный вид первого полинома: " << p1 << std::endl;

    std::cout << "Введите второй полином: ";
    std::cin >> p2;
    std::cout << "Нормализованный вид второго полинома: " << p2 << std::endl;

    // Сложение полиномов
    Polynomial sum_poly = p1 + p2;
    std::cout << "Сумма полиномов: " << sum_poly << std::endl;

    // Умножение полиномов
    Polynomial product_poly = p1 * p2;
    std::cout << "Произведение полиномов: " << product_poly << std::endl;

    return 0;
}
