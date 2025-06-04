#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include "Corvette.h"
#include "SailingShip.h"
#include "Steamship.h"
#include "lib/stack.h"

void print(const MyStack<Ship*>& container) {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    MyStack<Ship*> temp(container);
    std::size_t i = 0;

    while (!temp.empty()) {
        std::cout << "index " << i++ << ": ";
        temp.topInf()->show();
        temp.pop();
    }
}

void remove(MyStack<Ship*>& container, std::size_t index) {
    if (container.empty()) {
        std::cerr << "Контейнер пуст!" << std::endl;
        return;
    }

    MyStack<Ship*> temp;
    std::size_t currentSize = 0;

    MyStack<Ship*> counter(container);
    while (!counter.empty()) {
        currentSize++;
        counter.pop();
    }

    if (index >= currentSize) {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < index; ++i) {
        temp.push(container.topInf());
        container.pop();
    }

    Ship* toDelete = container.topInf();
    container.pop();
    delete toDelete;

    while (!temp.empty()) {
        container.push(temp.topInf());
        temp.pop();
    }
}

void clear(MyStack<Ship*>& container) {
    while (!container.empty()) {
        Ship* toDelete = container.topInf();
        container.pop();
        delete toDelete;
    }
}

int main() {
    MyStack<Ship*> container;
    int choice = -1;
    char bufferName[100];
    char bufferDetail[100];

    while (choice != 0) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить пароход\n"
                  << "2. Добавить парусник\n"
                  << "3. Добавить корвет\n"
                  << "4. Вывести все корабли\n"
                  << "5. Удалить по индексу\n"
                  << "6. Очистить контейнер\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите год постройки: ";
                int year;
                std::cin >> year;
                std::cin.ignore();

                std::cout << "Введите тип двигателя: ";
                std::cin.getline(bufferDetail, 100);

                container.push(new Steamship(bufferName, year, bufferDetail));
                break;
            }
            case 2: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите год постройки: ";
                int year;
                std::cin >> year;
                std::cin.ignore();

                std::cout << "Введите тип парусов: ";
                std::cin.getline(bufferDetail, 100);

                container.push(new SailingShip(bufferName, year, bufferDetail));
                break;
            }
            case 3: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите год постройки: ";
                int year;
                std::cin >> year;
                std::cin.ignore();

                std::cout << "Введите вооружение: ";
                std::cin.getline(bufferDetail, 100);

                container.push(new Corvette(bufferName, year, bufferDetail));
                break;
            }
            case 4:
                print(container);
                break;
            case 5: {
                std::size_t index;
                std::cout << "Введите индекс: ";
                std::cin >> index;
                remove(container, index);
                break;
            }
            case 6:
                clear(container);
                break;
            case 0:
                clear(container);
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    }

    return 0;
}
