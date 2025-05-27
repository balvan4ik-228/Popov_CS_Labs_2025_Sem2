#ifndef TERM_H
#define TERM_H

#include <iostream>

class Polynomial;

class Term {
private:
    int coefficient;
    int exponent;

public:
    Term();
    Term(int coef);
    Term(int coef, int exp);

    int getCoefficient() const;
    int getExponent() const;

    friend Term operator+(const Term& t1, const Term& t2);
    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);

    friend class Polynomial;
};

#endif // TERM_H
