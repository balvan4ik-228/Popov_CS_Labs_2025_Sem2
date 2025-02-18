#include "Planet/planet.h"
#include <iostream>
#include <iomanip>

int main() {
    Planet** planets = nullptr;
    int size = 0;

    int choice;
    char name[100];

    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Считать таблицу из файла" << std::endl;
        std::cout << "2. Добавить планету" << std::endl;
        std::cout << "3. Удалить планету" << std::endl;
        std::cout << "4. Сортировать по имени" << std::endl;
        std::cout << "5. Сортировать по диаметру" << std::endl;
        std::cout << "6. Сортировать по наличию жизни" << std::endl;
        std::cout << "7. Сортировать по количеству спутников" << std::endl;
        std::cout << "8. Редактировать планету" << std::endl;
        std::cout << "9. Вывести таблицу планет" << std::endl;
        std::cout << "10. Сохранить таблицу в файл" << std::endl; // Новый пункт меню
        std::cout << "0. Выход" << std::endl;

        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { // Считывание таблицы из файла
                char filename[100];
                std::cout << "Введите имя файла: ";
                std::cin >> filename;
                LoadPlanetsFromFile(planets, size, filename);
                break;
            }
            case 2:
                AddPlanet(planets, size);
                break;
            case 3:
                std::cout << "Введите имя планеты для удаления: ";
                std::cin >> name;
                DeletePlanet(planets, size, name);
                break;
            case 4:
                SortPlanetsByName(planets, size);
                PrintPlanetTable(planets, size);
                break;
            case 5:
                SortPlanetsByDiameter(planets, size);
                PrintPlanetTable(planets, size);
                break;
            case 6:
                SortPlanetsByLife(planets, size);
                PrintPlanetTable(planets, size);
                break;
            case 7:
                SortPlanetsBySatellites(planets, size);
                PrintPlanetTable(planets, size);
                break;
            case 8:
                std::cout << "Введите имя планеты для редактирования: ";
                std::cin >> name;
                EditPlanet(planets, size, name);
                break;
            case 9:
                PrintPlanetTable(planets, size);
                break;
            case 10: { // Сохранение таблицы в файл
                char filename[100];
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                SavePlanetsToFile(planets, size, filename);
                break;
            }
            case 0:
                for (int i = 0; i < size; ++i) {
                    delete[] planets[i]->name; // Освобождение памяти для имени
                    delete planets[i]; // Освобождение памяти для объекта
                }
                delete[] planets; // Освобождение памяти для массива указателей
                return 0;
            default:
                std::cout << "Неверный выбор." << std::endl;
        }
    }
}
