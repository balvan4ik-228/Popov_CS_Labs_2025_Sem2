#ifndef SAILINGSHIP_H
#define SAILINGSHIP_H

#include "Ship.h"
#include <cstring>

class SailingShip : public Ship {
protected:
    char* sailType;
public:
    SailingShip(const char* n, int y, const char* sail)
        : Ship(n, y) {
        sailType = new char[strlen(sail) + 1];
        strcpy(sailType, sail);
        std::cout << "SailingShip()" << std::endl;
    }

    ~SailingShip() override {
        delete[] sailType;
        std::cout << "~SailingShip()" << std::endl;
    }

    void show() const override {
        std::cout << "Парусник: " << name << ", год: " << year
            << ", паруса: " << sailType << std::endl;
    }
};

#endif
