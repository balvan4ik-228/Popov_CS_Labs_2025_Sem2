#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "../Term/Term.h"

class Polynomial {
private:
    Term* terms;
    int capacity;
    int size;
    int degree;
    bool order; // true — по убыванию, false — по возрастанию

    void resize();
    void addTerm(const Term& t);
    void insertTerm(const Term& t);
    void removeTerm(int index);
    void updateDegree();

public:
    Polynomial();
    Polynomial(int constant);
    Polynomial(const Term& t);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Term& t);
    Polynomial& operator+=(const Polynomial& other);

    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
    friend std::istream& operator>>(std::istream& is, Polynomial& p);
};

#endif // POLYNOMIAL_H
