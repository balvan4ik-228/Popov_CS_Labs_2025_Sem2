#include "Term.h"
#include <cctype>
#include <sstream>
#include <cstdlib>

// Вспомогательные функции для работы с C-строками
int findChar(const char* str, char c) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) return i;
        i++;
    }
    return -1; // Символ не найден
}

int TermStringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

char* substring(const char* str, int start, int length = -1) {
    int strLen = TermStringLength(str);

    if (start >= strLen) {
        char* result = new char[1];
        result[0] = '\0';
        return result;
    }

    if (length == -1 || start + length > strLen) {
        length = strLen - start;
    }

    char* result = new char[length + 1];
    for (int i = 0; i < length; i++) {
        result[i] = str[start + i];
    }
    result[length] = '\0';

    return result;
}

Term::Term() : coefficient(0), exponent(0) {}

Term::Term(int coef) : coefficient(coef), exponent(0) {}

Term::Term(int coef, int exp) : coefficient(coef), exponent(exp) {}

int Term::getCoefficient() const {
    return coefficient;
}

int Term::getExponent() const {
    return exponent;
}

Term operator+(const Term& t1, const Term& t2) {
    if (t1.exponent != t2.exponent) {
        throw std::invalid_argument("Cannot add terms with different exponents");
    }
    return Term(t1.coefficient + t2.coefficient, t1.exponent);
}

std::istream& operator>>(std::istream& is, Term& term) {
    // Читаем ввод во временный буфер
    char buffer[256];
    is >> buffer;

    // Создаем динамический массив точного размера
    int bufferLen = TermStringLength(buffer);
    char* input = new char[bufferLen + 1];
    for (int i = 0; i <= bufferLen; i++) {
        input[i] = buffer[i];
    }

    // Значения по умолчанию
    int coefficient = 1;
    int exponent = 0;

    // Проверка на пустую строку
    if (bufferLen == 0) {
        term = Term(0, 0);
        delete[] input;
        return is;
    }

    // Проверка на наличие 'x'
    int xPos = findChar(input, 'x');
    if (xPos == -1) {
        // Нет 'x', значит это просто число (коэффициент с нулевой степенью)
        coefficient = atoi(input);
        exponent = 0;
    } else {
        // Есть 'x', разбираем коэффициент
        if (xPos == 0) {
            // Если 'x' в начале, то коэффициент = 1
            coefficient = 1;
        } else if (xPos == 1 && input[0] == '-') {
            // Если '-x', то коэффициент = -1
            coefficient = -1;
        } else {
            // Иначе парсим коэффициент из подстроки до 'x'
            char* coeffStr = substring(input, 0, xPos);
            if (coeffStr[0] == '+' && coeffStr[1] == '\0') {
                coefficient = 1;
            } else if (coeffStr[0] == '-' && coeffStr[1] == '\0') {
                coefficient = -1;
            } else {
                coefficient = atoi(coeffStr);
            }
            delete[] coeffStr;
        }

        // Разбираем показатель степени
        if (xPos == bufferLen - 1) {
            // Если 'x' в конце, то степень = 1
            exponent = 1;
        } else if (input[xPos + 1] == '^') {
            // Если после 'x' идет '^', то парсим показатель
            char* expStr = substring(input, xPos + 2);
            exponent = atoi(expStr);
            delete[] expStr;
        } else {
            // Ошибка формата
            is.setstate(std::ios::failbit);
            delete[] input;
            return is;
        }
    }

    term = Term(coefficient, exponent);
    delete[] input;
    return is;
}



std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.exponent == 0) {
        os << term.coefficient;
    } else if (term.exponent == 1) {
        if (term.coefficient == 1) {
            os << "x";
        } else if (term.coefficient == -1) {
            os << "-x";
        } else {
            os << term.coefficient << "x";
        }
    } else {
        if (term.coefficient == 1) {
            os << "x^" << term.exponent;
        } else if (term.coefficient == -1) {
            os << "-x^" << term.exponent;
        } else {
            os << term.coefficient << "x^" << term.exponent;
        }
    }
    return os;
}
