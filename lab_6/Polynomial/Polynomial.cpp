#include "Polynomial.h"
#include <algorithm>
#include <sstream>

Polynomial::Polynomial() : capacity(10), size(0), degree(0), order(true) {
    terms = new Term[capacity];
}

Polynomial::Polynomial(int constant) : capacity(10), size(1), degree(0), order(true) {
    terms = new Term[capacity];
    terms[0] = Term(constant);
}

Polynomial::Polynomial(const Term& t) : capacity(10), size(1), degree(t.getExp()), order(true) {
    terms = new Term[capacity];
    terms[0] = t;
}

Polynomial::Polynomial(const Polynomial& other) : capacity(other.capacity), size(other.size), degree(other.degree), order(other.order) {
    terms = new Term[capacity];
    for (int i = 0; i < size; ++i) {
        terms[i] = other.terms[i];
    }
}

Polynomial::~Polynomial() {
    delete[] terms;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] terms;
        capacity = other.capacity;
        size = other.size;
        degree = other.degree;
        order = other.order;
        terms = new Term[capacity];
        for (int i = 0; i < size; ++i) {
            terms[i] = other.terms[i];
        }
    }
    return *this;
}

void Polynomial::resize() {
    capacity *= 2;
    Term* newTerms = new Term[capacity];
    for (int i = 0; i < size; ++i) {
        newTerms[i] = terms[i];
    }
    delete[] terms;
    terms = newTerms;
}

void Polynomial::addTerm(const Term& t) {
    if (t.getCoeff() == 0) return;

    for (int i = 0; i < size; ++i) {
        if (terms[i].getExp() == t.getExp()) {
            terms[i] = terms[i] + t;
            if (terms[i].getCoeff() == 0) {
                removeTerm(i);
            }
            updateDegree();
            return;
        }
    }

    insertTerm(t);
    updateDegree();
}

void Polynomial::insertTerm(const Term& t) {
    if (size == capacity) resize();

    int pos = 0;
    while (pos < size && ((order && terms[pos].getExp() > t.getExp()) || (!order && terms[pos].getExp() < t.getExp()))) {
        pos++;
    }

    for (int i = size; i > pos; --i) {
        terms[i] = terms[i - 1];
    }

    terms[pos] = t;
    size++;
}

void Polynomial::removeTerm(int index) {
    for (int i = index; i < size - 1; ++i) {
        terms[i] = terms[i + 1];
    }
    size--;
}

void Polynomial::updateDegree() {
    degree = 0;
    for (int i = 0; i < size; ++i) {
        if (terms[i].getExp() > degree) {
            degree = terms[i].getExp();
        }
    }
}

Polynomial& Polynomial::operator+=(const Term& t) {
    addTerm(t);
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) {
        addTerm(other.terms[i]);
    }
    return *this;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result(p1);
    result += p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result;
    for (int i = 0; i < p1.size; ++i) {
        for (int j = 0; j < p2.size; ++j) {
            Term t(p1.terms[i].getCoeff() * p2.terms[j].getCoeff(),
                   p1.terms[i].getExp() + p2.terms[j].getExp());
            result += t;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.size == 0) {
        os << "0";
        return os;
    }

    bool first = true;
    for (int i = 0; i < p.size; ++i) {
        Term t = p.terms[i];
        if (t.getCoeff() == 0) continue;

        if (!first) {
            os << (t.getCoeff() > 0 ? " + " : " - ");
            if (t.getCoeff() > 0) {
                os << Term(t.getCoeff(), t.getExp());
            } else {
                os << Term(-t.getCoeff(), t.getExp());
            }
        } else {
            os << t;
            first = false;
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    std::string line;
    std::getline(is, line);

    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

    if (line.empty()) {
        p = Polynomial();
        return is;
    }

    if (line[0] != '+' && line[0] != '-') {
        line = '+' + line;
    }

    size_t start = 0;
    while (start < line.size()) {
        size_t end = line.find_first_of("+-", start + 1);
        if (end == std::string::npos) end = line.size();
        std::string token = line.substr(start, end - start);
        start = end;

        std::istringstream iss(token);
        Term t;
        if (iss >> t) {
            p += t;
        } else {
            is.setstate(std::ios::failbit);
            break;
        }
    }

    return is;
}
