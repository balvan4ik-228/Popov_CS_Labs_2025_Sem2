#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "../Term/Term.h"

class Polynomial {
private:
    Term* terms;      // Динамический массив термов
    int capacity;     // Вместимость массива
    int size;         // Текущий размер
    int degree;       // Степень полинома
    bool order;       // true — сортировка по убыванию степени

    void resize();          // Увеличение размера массива
    void addTerm(const Term& t); // Добавление терма
    void insertTerm(const Term& t); // Вставка с сортировкой
    void removeTerm(int index);    // Удаление терма
    void updateDegree();           // Обновление степени полинома

public:
    Polynomial();                   // Конструктор по умолчанию (0)
    Polynomial(int constant);       // Конструктор для константы
    Polynomial(const Term& t);      // Конструктор из терма
    Polynomial(const Polynomial& other); // Конструктор копирования
    ~Polynomial();

    Polynomial& operator=(const Polynomial& other); // Присваивание
    Polynomial& operator+=(const Term& t);          // Добавление терма
    Polynomial& operator+=(const Polynomial& other); // Сложение полиномов

    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2); // Сложение
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2); // Умножение

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p); // Вывод
    friend std::istream& operator>>(std::istream& is, Polynomial& p);       // Ввод
};

#endif // POLYNOMIAL_H
