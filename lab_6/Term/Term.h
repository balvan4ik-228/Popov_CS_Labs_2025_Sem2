#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <stdexcept>

class Term {
private:
    int coeff;
    int exp;

public:
    Term();
    Term(int c);
    Term(int c, int e);

    friend Term operator+(const Term& t1, const Term& t2);

    friend std::ostream& operator<<(std::ostream& os, const Term& t);
    friend std::istream& operator>>(std::istream& is, Term& t);

    int getCoeff() const;
    int getExp() const;

    // Проверка на валидность степени (опционально)
    bool isValid() const;
};

#endif // TERM_H
