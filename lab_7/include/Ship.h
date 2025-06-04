#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <cstring>

class Ship {
protected:
    char *name;
    int year;

public:
    Ship(const char* n, int y) : year(y) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        std::cout << "Ship()" << std::endl;
    }

    virtual ~Ship() {
        delete[] name;
        std::cout << "~Ship()" << std::endl;
    }

    virtual void show() const = 0;
};

#endif
