#ifndef STEAMSHIP_H
#define STEAMSHIP_H

#include "Ship.h"
#include <cstring>

class Steamship : public Ship {
protected:
    char* engineType;
public:
    Steamship(const char* n, int y, const char* eng)
        : Ship(n, y) {
        engineType = new char[strlen(eng) + 1];
        strcpy(engineType, eng);
        std::cout << "Steamship()" << std::endl;
    }

    ~Steamship() override {
        delete[] engineType;
        std::cout << "~Steamship()" << std::endl;
    }

    void show() const override {
        std::cout << "Пароход: " << name << ", год: " << year
            << ", двигатель: " << engineType << std::endl;
    }
};

#endif
