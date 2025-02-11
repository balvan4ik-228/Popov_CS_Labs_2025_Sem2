#include <iostream>
#include "mymath/mymath.h"

int main() {
    std::cout << "Я умею суммировать! Зацени 1+1=";
    std::cout << mymath::sum(10, 32) << std::endl;

    std::cout << "Я умею умножать! 26*2=";
    std::cout << mymath::times(26, 2) << std::endl;

    return 0;
}
