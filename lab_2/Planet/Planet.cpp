#include "Planet.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cstring>

Planet::Planet() : name(nullptr), diameter(0), satellites(0), hasLife(false) {}

Planet::Planet(const char* name, long long diameter, int satellites, bool hasLife)
    : diameter(diameter), satellites(satellites), hasLife(hasLife) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Planet::Planet(const Planet& other) : name(nullptr) {
    copyFrom(other);
}

Planet::~Planet() {
    cleanup();
}

Planet& Planet::operator=(const Planet& other) {
    if(this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

void Planet::copyFrom(const Planet& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    diameter = other.diameter;
    satellites = other.satellites;
    hasLife = other.hasLife;
}

void Planet::cleanup() {
    delete[] name;
    name = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << std::left
       << planet.name << " "
       << planet.diameter << " "
       << planet.satellites << " "
       << (planet.hasLife ? "Да" : "Нет");
    return os;
}

std::istream& operator>>(std::istream& is, Planet& planet) {
    char name[100];
    long long diameter;
    int satellites;
    int lifeFlag;

    std::cout << "\n=== Ввод данных планеты ===\n";
    std::cout << "Название: ";
    is.ignore();
    is.getline(name, 100);

    std::cout << "Диаметр: ";
    is >> diameter;

    std::cout << "Спутники: ";
    is >> satellites;

    std::cout << "Наличие жизни (1 - Да, 0 - Нет): ";
    is >> lifeFlag;
    while(lifeFlag != 0 && lifeFlag != 1) {
        std::cout << "Неверный ввод! Введите 0 или 1: ";
        is >> lifeFlag;
    }

    delete[] planet.name;
    planet.name = new char[strlen(name) + 1];
    strcpy(planet.name, name);
    planet.diameter = diameter;
    planet.satellites = satellites;
    planet.hasLife = (lifeFlag == 1);

    return is;
}

void Planet::readFromFile(Planet*& planets, int& size) {
    const char* filename = "Planets.txt";
    std::ifstream file(filename);
    if(!file) {
        std::cerr << "Ошибка открытия файла " << filename << "\n";
        return;
    }

    Planet temp[100];
    int count = 0;
    std::string line;

    while(std::getline(file, line) && count < 100) {
        std::istringstream iss(line);
        std::string name;
        long long diameter;
        int satellites;
        std::string lifeStr;

        if(iss >> name >> diameter >> satellites >> lifeStr) {
            bool hasLife = (lifeStr == "Да");
            temp[count++] = Planet(name.c_str(), diameter, satellites, hasLife);
        }
    }

    if(count > 0) {
        delete[] planets;
        planets = new Planet[count];
        for(int i = 0; i < count; ++i) {
            planets[i] = temp[i];
        }
        size = count;
    }
    file.close();
}

void Planet::writeToFile(const Planet* planets, int size) {
    const char* filename = "Planets.txt";
    std::ofstream file(filename);
    if(!file) {
        std::cerr << "Ошибка создания файла " << filename << "\n";
        return;
    }

    for(int i = 0; i < size; ++i) {
        file << std::setw(15) << planets[i].name << " "
             << std::setw(15) << planets[i].diameter << " "
             << std::setw(15) << planets[i].satellites << " "
             << std::setw(10) << (planets[i].hasLife ? "Да" : "Нет") << "\n";
    }
    file.close();
}

void Planet::sortPlanets(Planet* planets, int size, int sortBy, bool descending) {
    auto compare = [sortBy, descending](const Planet& a, const Planet& b) {
        switch(sortBy) {
            case 1: return descending ? strcmp(a.name, b.name) > 0 : strcmp(a.name, b.name) < 0;
            case 2: return descending ? a.diameter > b.diameter : a.diameter < b.diameter;
            case 3: return descending ? a.satellites > b.satellites : a.satellites < b.satellites;
            case 4: return descending ? a.hasLife > b.hasLife : a.hasLife < b.hasLife;
            default: return false;
        }
    };
    std::sort(planets, planets + size, compare);
}

void Planet::addPlanet(Planet*& planets, int& size, const Planet& newPlanet) {
    if(size >= 100) {
        std::cout << "Достигнут лимит в 100 планет!\n";
        return;
    }
    Planet* newArray = new Planet[size + 1];
    for(int i = 0; i < size; ++i) {
        newArray[i] = planets[i];
    }
    newArray[size] = newPlanet;
    delete[] planets;
    planets = newArray;
    ++size;
}

void Planet::removePlanet(Planet*& planets, int& size, const char* planetName) {
    bool found = false;
    for(int i = 0; i < size; ++i) {
        if(strcmp(planets[i].name, planetName) == 0) {
            found = true;
            for(int j = i; j < size - 1; ++j) {
                planets[j] = planets[j + 1];
            }
            --size;
            break;
        }
    }

    if(!found) {
        std::cout << "Планета '" << planetName << "' не найдена!\n";
        return;
    }

    Planet* newArray = new Planet[size];
    for(int i = 0; i < size; ++i) {
        newArray[i] = planets[i];
    }
    delete[] planets;
    planets = newArray;
}

void Planet::editPlanetByName(Planet* planets, int size, const char* planetName) {
    bool found = false;
    for(int i = 0; i < size; ++i) {
        if(strcmp(planets[i].name, planetName) == 0) {
            found = true;
            std::cout << "Текущие данные планеты:\n";
            std::cout << planets[i] << "\n";
            std::cout << "Введите новые данные:\n";
            std::cin >> planets[i];
            break;
        }
    }

    if(!found) {
        std::cout << "Планета '" << planetName << "' не найдена!\n";
    }
}

void Planet::displayPlanets(const Planet* planets, int size) {
    if(size == 0) {
        std::cout << "Список планет пуст!\n";
        return;
    }

    std::cout << "\n" << std::string(65, '=') << "\n";
    std::cout << std::left
              << std::setw(23) << "Название"
              << std::setw(22) << "Диаметр"
              << std::setw(23) << "Спутники"
              << std::setw(10) << "Жизнь"
              << "\n";
    std::cout << std::string(65, '-') << "\n";

    for(int i = 0; i < size; ++i) {
        std::cout << std::setw(15) << planets[i].name
                  << std::setw(15) << planets[i].diameter
                  << std::setw(15) << planets[i].satellites
                  << std::setw(10) << (planets[i].hasLife ? "Да" : "Нет")
                  << "\n";
    }

    std::cout << std::string(65, '=') << "\n";
}
