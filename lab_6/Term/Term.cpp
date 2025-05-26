#include "Term.h"
#include <sstream>
#include <cctype>

Term::Term() : coeff(0), exp(0) {}
Term::Term(int c) : coeff(c), exp(0) {}
Term::Term(int c, int e) : coeff(c), exp(e) {}

// Сложение термов (разрешены любые степени)
Term operator+(const Term& t1, const Term& t2) {
    if (t1.exp != t2.exp) {
        throw std::invalid_argument("Степени термов должны совпадать!");
    }
    return Term(t1.coeff + t2.coeff, t1.exp);
}

// Вывод терма с отрицательными степенями
std::ostream& operator<<(std::ostream& os, const Term& t) {
    if (t.coeff == 0) {
        os << "0";
        return os;
    }

    // Коэффициент
    if ((t.coeff != 1 && t.coeff != -1) || t.exp == 0) {
        os << t.coeff;
    } else if (t.coeff == -1) {
        os << "-";
    }

    // Переменная и степень
    if (t.exp != 0) {
        os << "x";
        if (t.exp != 1) {
            os << "^" << t.exp; // Например: x^-2
        }
    }
    return os;
}

// Ввод термов с отрицательными степенями
std::istream& operator>>(std::istream& is, Term& t) {
    char sign = '+';
    int coeff = 0, exp = 0;
    char ch;

    // Пропуск пробелов
    while (is.get(ch) && std::isspace(ch)) {}

    // Знак
    if (ch == '+' || ch == '-') {
        sign = ch;
        if (std::isspace(is.peek())) {
            coeff = (sign == '-' ? -1 : 1);
            t = Term(coeff, 0);
            return is;
        }
    } else {
        is.putback(ch);
    }

    // Коэффициент
    if (std::isdigit(is.peek())) {
        is >> coeff;
    } else if (is.peek() == 'x') {
        coeff = 1;
    } else {
        coeff = (sign == '-' ? -1 : 1);
    }

    coeff *= (sign == '-' ? -1 : 1);

    // Степень
    if (is.peek() == 'x') {
        is.get();
        exp = 1;
        if (is.peek() == '^') {
            is.get();
            is >> exp; // Считывает отрицательные степени
        }
    }

    t = Term(coeff, exp);
    return is;
}

int Term::getCoeff() const { return coeff; }
int Term::getExp() const { return exp; }

// Проверка на валидность (опционально)
bool Term::isValid() const {
    return true; // Разрешены любые степени
}
