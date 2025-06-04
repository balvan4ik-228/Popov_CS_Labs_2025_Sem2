#ifndef CORVETTE_H
#define CORVETTE_H

#include "Ship.h"
#include <cstring>

class Corvette : public Ship {
protected:
    char* weapon;
public:
    Corvette(const char* n, int y, const char* w)
        : Ship(n, y) {
        weapon = new char[strlen(w) + 1];
        strcpy(weapon, w);
        std::cout << "Corvette()" << std::endl;
    }

    ~Corvette() override {
        delete[] weapon;
        std::cout << "~Corvette()" << std::endl;
    }

    void show() const override {
        std::cout << "Корвет: " << name << ", год: " << year
            << ", вооружение: " << weapon << std::endl;
    }
};

#endif
