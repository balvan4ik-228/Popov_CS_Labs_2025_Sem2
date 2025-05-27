#include "Polynomial.h"
#include <sstream>
#include <cctype>

int PolyStringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* createString(int size) {
    char* str = new char[size + 1];
    str[0] = '\0';
    return str;
}

char* stringCopy(const char* source) {
    int length = PolyStringLength(source);
    char* dest = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        dest[i] = source[i];
    }
    return dest;
}

bool stringEmpty(const char* str) {
    return str[0] == '\0';
}

Polynomial::Polynomial() : poly(nullptr), size(0), degree(0), ascending(true) {
    poly = new Term[1];
    poly[0] = Term(0, 0);
    size = 1;
}

Polynomial::Polynomial(int constant) : poly(nullptr), size(0), degree(0), ascending(true) {
    poly = new Term[1];
    poly[0] = Term(constant, 0);
    size = 1;
}

Polynomial::Polynomial(const Term& term) : poly(nullptr), size(0), degree(0), ascending(true) {
    poly = new Term[1];
    poly[0] = term;
    size = 1;
    degree = term.getExponent();
}

Polynomial::Polynomial(const Polynomial& other) : poly(nullptr), size(other.size), degree(other.degree), ascending(other.ascending) {
    poly = new Term[size];
    for (int i = 0; i < size; i++) {
        poly[i] = other.poly[i];
    }
}

Polynomial::~Polynomial() {
    delete[] poly;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    char buffer[1024];
    is.getline(buffer, 1024);

    // Очистка существующего полинома
    if (poly.poly != nullptr) {
        delete[] poly.poly;
        poly.poly = nullptr;
    }

    // Временное хранение термов
    Term* terms = new Term[100]; // Предполагаем максимум 100 термов
    int termCount = 0;

    // Текущий терм в виде динамического массива
    char* currTerm = createString(100);
    int currTermLength = 0;
    bool positive = true;

    // Добавляем "+" в начало, если строка не начинается с "+" или "-"
    char* line;
    if (buffer[0] != '\0' && buffer[0] != '+' && buffer[0] != '-') {
        int bufferLen = PolyStringLength(buffer);
        line = new char[bufferLen + 2];
        line[0] = '+';
        for (int i = 0; i <= bufferLen; i++) {
            line[i + 1] = buffer[i];
        }
    } else {
        line = stringCopy(buffer);
    }

    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];

        if (c == '+' || c == '-') {
            // Обработка предыдущего терма, если он есть
            if (currTermLength > 0) {
                currTerm[currTermLength] = '\0';
                std::istringstream iss(currTerm);
                Term term;
                iss >> term;

                if (!positive) {
                    term = Term(-term.getCoefficient(), term.getExponent());
                }

                // Добавляем терм к полиному
                terms[termCount++] = term;
                currTermLength = 0;
            }

            positive = (c == '+');
        }
        else if (!std::isspace(c)) {
            currTerm[currTermLength++] = c;
        }
    }

    // Обработка последнего терма
    if (currTermLength > 0) {
        currTerm[currTermLength] = '\0';
        std::istringstream iss(currTerm);
        Term term;
        iss >> term;

        if (!positive) {
            term = Term(-term.getCoefficient(), term.getExponent());
        }

        terms[termCount++] = term;
    }

    delete[] currTerm;
    delete[] line;

    // Объединение термов с одинаковыми степенями
    for (int i = 0; i < termCount; i++) {
        if (terms[i].getCoefficient() == 0) continue;

        for (int j = i + 1; j < termCount; j++) {
            if (terms[j].getExponent() == terms[i].getExponent()) {
                // Объединяем термы
                terms[i] = terms[i] + terms[j];
                terms[j] = Term(0, terms[j].getExponent()); // Обнуляем коэффициент
            }
        }
    }


    // Подсчет ненулевых термов
    int nonZeroCount = 0;
    for (int i = 0; i < termCount; i++) {
        if (terms[i].getCoefficient() != 0) {
            nonZeroCount++;
        }
    }

    // Создание нового полинома с ненулевыми термами
    poly.poly = new Term[nonZeroCount];
    poly.size = nonZeroCount;

    // Копирование ненулевых термов и определение степени полинома
    int index = 0;
    poly.degree = 0;
    for (int i = 0; i < termCount; i++) {
        if (terms[i].getCoefficient() != 0) {
            poly.poly[index++] = terms[i];
            if (terms[i].getExponent() > poly.degree) {
                poly.degree = terms[i].getExponent();
            }
        }
    }

    // Сортировка термов по степеням (по возрастанию или убыванию)
    for (int i = 0; i < poly.size - 1; i++) {
        for (int j = 0; j < poly.size - i - 1; j++) {
            if ((poly.ascending && poly.poly[j].getExponent() > poly.poly[j+1].getExponent()) ||
                (!poly.ascending && poly.poly[j].getExponent() < poly.poly[j+1].getExponent())) {
                // Меняем местами
                Term temp = poly.poly[j];
                poly.poly[j] = poly.poly[j+1];
                poly.poly[j+1] = temp;
            }
        }
    }

    delete[] terms;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    bool first = true;
    bool anyTermPrinted = false;

    // Если используется сортировка по убыванию степени
    if (!poly.ascending) {
        for (int i = 0; i < poly.size; i++) {
            if (poly.poly[i].getCoefficient() == 0) {
                continue; // Пропускаем члены с нулевым коэффициентом
            }

            anyTermPrinted = true;

            if (!first) {
                if (poly.poly[i].getCoefficient() > 0) {
                    os << " + ";
                } else {
                    os << " - ";
                }
            } else if (poly.poly[i].getCoefficient() < 0) {
                os << "-";
            }

            int absCoef = poly.poly[i].getCoefficient() > 0 ?
                          poly.poly[i].getCoefficient() :
                         -poly.poly[i].getCoefficient();

            if (poly.poly[i].getExponent() == 0) {
                os << absCoef;
            } else if (poly.poly[i].getExponent() == 1) {
                if (absCoef == 1) {
                    os << "x";
                } else {
                    os << absCoef << "x";
                }
            } else {
                if (absCoef == 1) {
                    os << "x^" << poly.poly[i].getExponent();
                } else {
                    os << absCoef << "x^" << poly.poly[i].getExponent();
                }
            }

            first = false;
        }
    }
    // Если используется сортировка по возрастанию степени
    else {
        // Начинаем с конца массива (высшие степени)
        for (int i = poly.size - 1; i >= 0; i--) {
            if (poly.poly[i].getCoefficient() == 0) {
                continue; // Пропускаем члены с нулевым коэффициентом
            }

            anyTermPrinted = true;

            if (!first) {
                if (poly.poly[i].getCoefficient() > 0) {
                    os << " + ";
                } else {
                    os << " - ";
                }
            } else if (poly.poly[i].getCoefficient() < 0) {
                os << "-";
            }

            int absCoef = poly.poly[i].getCoefficient() > 0 ?
                          poly.poly[i].getCoefficient() :
                         -poly.poly[i].getCoefficient();


            if (poly.poly[i].getExponent() == 0) {
                os << absCoef;
            } else if (poly.poly[i].getExponent() == 1) {
                if (absCoef == 1) {
                    os << "x";
                } else {
                    os << absCoef << "x";
                }
            } else {
                if (absCoef == 1) {
                    os << "x^" << poly.poly[i].getExponent();
                } else {
                    os << absCoef << "x^" << poly.poly[i].getExponent();
                }
            }

            first = false;
        }
    }

    // Если не было выведено ни одного терма, выводим 0
    if (!anyTermPrinted) {
        os << "0";
    }

    return os;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    // Создаем полином с достаточным размером для хранения всех термов
    Polynomial result;
    delete[] result.poly;
    result.poly = new Term[lhs.size + rhs.size];
    result.size = 0;
    result.degree = 0;
    result.ascending = lhs.ascending; // Сохраняем порядок сортировки

    // Копируем термы из первого полинома
    for (int i = 0; i < lhs.size; i++) {
        result.poly[result.size++] = lhs.poly[i];
        if (lhs.poly[i].getExponent() > result.degree) {
            result.degree = lhs.poly[i].getExponent();
        }
    }

    // Добавляем термы из второго полинома
    for (int i = 0; i < rhs.size; i++) {
        bool termExists = false;

        // Проверяем, есть ли уже терм с такой степенью
        for (int j = 0; j < result.size; j++) {
            if (result.poly[j].getExponent() == rhs.poly[i].getExponent()) {
                // Складываем коэффициенты
                result.poly[j] = Term(
                    result.poly[j].getCoefficient() + rhs.poly[i].getCoefficient(),
                    rhs.poly[i].getExponent()
                );
                termExists = true;
                break;
            }
        }

        // Если терма с такой степенью нет, добавляем новый
        if (!termExists) {
            result.poly[result.size++] = rhs.poly[i];
            if (rhs.poly[i].getExponent() > result.degree) {
                result.degree = rhs.poly[i].getExponent();
            }
        }
    }

    // Подсчет ненулевых термов
    int nonZeroCount = 0;
    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            nonZeroCount++;
        }
    }

    // Создаем новый массив только с ненулевыми термами
    Term* newPoly = new Term[nonZeroCount];
    int newIndex = 0;

    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            newPoly[newIndex++] = result.poly[i];
        }
    }

    delete[] result.poly;
    result.poly = newPoly;
    result.size = nonZeroCount;

    // Сортировка термов по степеням
    for (int i = 0; i < result.size - 1; i++) {
        for (int j = 0; j < result.size - i - 1; j++) {
            if ((result.ascending && result.poly[j].getExponent() > result.poly[j+1].getExponent()) ||
                (!result.ascending && result.poly[j].getExponent() < result.poly[j+1].getExponent())) {
                // Меняем местами
                Term temp = result.poly[j];
                result.poly[j] = result.poly[j+1];
                result.poly[j+1] = temp;
            }
        }
    }
    return result;
}

Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) {
    // Создаем полином с достаточным размером для хранения всех термов
    Polynomial result;
    delete[] result.poly;
    result.poly = new Term[lhs.size + rhs.size];
    result.size = 0;
    result.degree = 0;
    result.ascending = lhs.ascending; // Сохраняем порядок сортировки

    // Копируем термы из первого полинома
    for (int i = 0; i < lhs.size; i++) {
        result.poly[result.size++] = lhs.poly[i];
        if (lhs.poly[i].getExponent() > result.degree) {
            result.degree = lhs.poly[i].getExponent();
        }
    }


    // Вычитаем термы из второго полинома
    for (int i = 0; i < rhs.size; i++) {
        bool termExists = false;

        // Проверяем, есть ли уже терм с такой степенью
        for (int j = 0; j < result.size; j++) {
            if (result.poly[j].getExponent() == rhs.poly[i].getExponent()) {
                // Вычитаем коэффициенты
                result.poly[j] = Term(
                    result.poly[j].getCoefficient() - rhs.poly[i].getCoefficient(),
                    rhs.poly[i].getExponent()
                );
                termExists = true;
                break;
            }
        }

        // Если терма с такой степенью нет, добавляем новый с отрицательным коэффициентом
        if (!termExists) {
            result.poly[result.size++] = Term(-rhs.poly[i].getCoefficient(), rhs.poly[i].getExponent());
            if (rhs.poly[i].getExponent() > result.degree) {
                result.degree = rhs.poly[i].getExponent();
            }
        }
    }

    // Подсчет ненулевых термов
    int nonZeroCount = 0;
    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            nonZeroCount++;
        }
    }

    // Создаем новый массив только с ненулевыми термами
    Term* newPoly = new Term[nonZeroCount];
    int newIndex = 0;

    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            newPoly[newIndex++] = result.poly[i];
        }
    }

    delete[] result.poly;
    result.poly = newPoly;
    result.size = nonZeroCount;

    // Сортировка термов по степеням
    for (int i = 0; i < result.size - 1; i++) {
        for (int j = 0; j < result.size - i - 1; j++) {
            if ((result.ascending && result.poly[j].getExponent() > result.poly[j+1].getExponent()) ||
                (!result.ascending && result.poly[j].getExponent() < result.poly[j+1].getExponent())) {
                // Меняем местами
                Term temp = result.poly[j];
                result.poly[j] = result.poly[j+1];
                result.poly[j+1] = temp;
            }
        }
    }

    return result;
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    // Если один из полиномов равен 0, результат будет 0
    if (lhs.size == 0 || rhs.size == 0) {
        return Polynomial(0);
    }

    // Создаем полином с достаточным размером для всех возможных термов
    Polynomial result;
    delete[] result.poly;
    // Максимальное количество термов - произведение размеров
    result.poly = new Term[lhs.size * rhs.size];
    result.size = 0;
    result.degree = 0;
    result.ascending = lhs.ascending; // Сохраняем порядок сортировки

    // Перемножаем каждый терм первого полинома с каждым термом второго
    for (int i = 0; i < lhs.size; i++) {
        for (int j = 0; j < rhs.size; j++) {
            // Умножаем коэффициенты и складываем степени
            int newCoef = lhs.poly[i].getCoefficient() * rhs.poly[j].getCoefficient();
            int newExp = lhs.poly[i].getExponent() + rhs.poly[j].getExponent();

            // Ищем, есть ли уже терм с такой степенью
            bool termExists = false;
            for (int k = 0; k < result.size; k++) {
                if (result.poly[k].getExponent() == newExp) {
                    // Если терм с такой степенью уже есть, добавляем коэффициент
                    result.poly[k] = Term(
                        result.poly[k].getCoefficient() + newCoef,
                        newExp
                    );
                    termExists = true;
                    break;
                }
            }

            // Если терма с такой степенью нет, добавляем новый
            if (!termExists && newCoef != 0) {
                result.poly[result.size++] = Term(newCoef, newExp);
                if (newExp > result.degree) {
                    result.degree = newExp;
                }
            }
        }
    }


    // Подсчет ненулевых термов
    int nonZeroCount = 0;
    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            nonZeroCount++;
        }
    }

    // Если все коэффициенты оказались нулевыми, возвращаем нулевой полином
    if (nonZeroCount == 0) {
        delete[] result.poly;
        result.poly = new Term[1];
        result.poly[0] = Term(0, 0);
        result.size = 1;
        result.degree = 0;
        return result;
    }

    // Создаем новый массив только с ненулевыми термами
    Term* newPoly = new Term[nonZeroCount];
    int newIndex = 0;

    for (int i = 0; i < result.size; i++) {
        if (result.poly[i].getCoefficient() != 0) {
            newPoly[newIndex++] = result.poly[i];
        }
    }

    delete[] result.poly;
    result.poly = newPoly;
    result.size = nonZeroCount;

    // Сортировка термов по степеням
    for (int i = 0; i < result.size - 1; i++) {
        for (int j = 0; j < result.size - i - 1; j++) {
            if ((result.ascending && result.poly[j].getExponent() > result.poly[j+1].getExponent()) ||
                (!result.ascending && result.poly[j].getExponent() < result.poly[j+1].getExponent())) {
                // Меняем местами
                Term temp = result.poly[j];
                result.poly[j] = result.poly[j+1];
                result.poly[j+1] = temp;
            }
        }
    }

    return result;
}
