#include "Tasks/Tasks.h"
#include <iostream>

int main() {
    int choice;
    while (true) {
        std::cout << "\nВыберите задание (1-9) или 0 для выхода: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            default:
                std::cout << "Неверный выбор!\n";
        }
    }
    return 0;
}
