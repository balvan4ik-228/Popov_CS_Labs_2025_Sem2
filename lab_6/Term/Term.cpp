#include "Term.h"
#include <sstream>
#include <cctype>

Term::Term() : coeff(0), exp(0) {}
Term::Term(int c) : coeff(c), exp(0) {}
Term::Term(int c, int e) : coeff(c), exp(e) {}

Term operator+(const Term& t1, const Term& t2) {
    if (t1.exp != t2.exp) {
        throw std::invalid_argument("Exponents must be equal for addition");
    }
    return Term(t1.coeff + t2.coeff, t1.exp);
}

std::ostream& operator<<(std::ostream& os, const Term& t) {
    if (t.coeff == 0) {
        os << "0";
        return os;
    }

    if (t.coeff != 1 && t.coeff != -1 || t.exp == 0) {
        if (t.exp == 0) {
            os << t.coeff;
        } else {
            os << t.coeff;
        }
    } else if (t.coeff == -1) {
        os << "-";
    }

    if (t.exp > 0) {
        os << "x";
        if (t.exp > 1) {
            os << "^" << t.exp;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Term& t) {
    char sign = '+';
    int coeff = 0;
    int exp = 0;
    char ch;

    while (is.get(ch) && std::isspace(ch)) {}

    if (ch == '+' || ch == '-') {
        sign = ch;
        if (!is.peek() || std::isspace(is.peek())) {
            coeff = (sign == '-' ? -1 : 1);
            is.putback(ch);
            return is;
        }
    } else {
        is.putback(ch);
    }

    if (std::isdigit(is.peek())) {
        is >> coeff;
    } else if (is.peek() == 'x') {
        coeff = 1;
    } else {
        coeff = (sign == '-' ? -1 : 1);
    }

    if (sign == '-') {
        coeff *= -1;
    }

    if (is.peek() == 'x') {
        is.get();
        exp = 1;
        if (is.peek() == '^') {
            is.get();
            is >> exp;
        }
    } else {
        exp = 0;
    }

    t = Term(coeff, exp);
    return is;
}

int Term::getCoeff() const { return coeff; }
int Term::getExp() const { return exp; }
