#include "planet.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

Planet::Planet() : name(nullptr), diameter(0.0), hasLife(false), numSatellites(0) {}

Planet::Planet(const char* name, double diameter, bool hasLife, int numSatellites) :
    diameter(diameter), hasLife(hasLife), numSatellites(numSatellites) {
    int len = std::strlen(name);
    this->name = new char[len + 1];
    std::strcpy(this->name, name);
}

Planet::Planet(const Planet& other) :
    diameter(other.diameter), hasLife(other.hasLife), numSatellites(other.numSatellites) {
    int len = std::strlen(other.name);
    this->name = new char[len + 1];
    std::strcpy(this->name, other.name);
}

Planet::~Planet() {
    delete[] name;
}

Planet& Planet::operator=(const Planet& other) {
    if (this != &other) {
        delete[] name;
        diameter = other.diameter;
        hasLife = other.hasLife;
        numSatellites = other.numSatellites;
        int len = std::strlen(other.name);
        name = new char[len + 1];
        std::strcpy(name, other.name);
    }
    return *this;
}

void AddPlanet(Planet**& planets, int& size) {
    Planet** newPlanets = new Planet*[size + 1];
    for (int i = 0; i < size; ++i) {
        newPlanets[i] = planets[i];
    }
    delete[] planets;
    planets = newPlanets;

    planets[size] = new Planet();

    char name[100];
    double diameter;
    bool hasLife;
    int numSatellites;

    std::cout << "Введите имя планеты: ";
    std::cin >> name;

    int len = std::strlen(name);

    planets[size]->name = new char[len + 1];

    std::strcpy(planets[size]->name, name);

    std::cout << "Введите диаметр планеты: ";
    std::cin >> diameter;

    planets[size]->diameter = diameter;

    std::cout << "Есть ли жизнь на планете? (1 - Да, 0 - Нет): ";

  	std::cin >> hasLife;

  	planets[size]->hasLife = hasLife;

  	std::cout << "Введите количество спутников: ";
  	std::cin >> numSatellites;

  	planets[size]->numSatellites = numSatellites;

  	size++;
}

void DeletePlanet(Planet**& planets, int& size, const char* name) {
   int indexToDelete = -1;
   for (int i = 0; i < size; ++i) {
       if (std::strcmp(planets[i]->name, name) == 0) {
           indexToDelete = i;
           break;
       }
   }

   if (indexToDelete == -1) {
       std::cout << "Планета не найдена." << std::endl;
       return;
   }

   delete planets[indexToDelete];
   for (int i = indexToDelete; i < size - 1; ++i) {
       planets[i] = planets[i + 1];
   }

   Planet** newPlanets = new Planet*[size - 1];
   for (int i = 0; i < size - 1; ++i) {
       newPlanets[i] = planets[i];
   }
   delete[] planets;
   planets = newPlanets;
   size--;

   std::cout << "Планета успешно удалена." << std::endl;
}

void SortPlanetsByName(Planet** planets, int size) {
   for (int i = 0; i < size - 1; ++i) {
       for (int j = 0; j < size - i - 1; ++j) {
           if (std::strcmp(planets[j]->name, planets[j + 1]->name) > 0) {
               Planet* temp = planets[j];
               planets[j] = planets[j + 1];
               planets[j + 1] = temp;
           }
       }
   }
}

void SortPlanetsByDiameter(Planet** planets, int size) {
   for (int i = 0; i < size - 1; ++i) {
       for (int j = 0; j < size - i - 1; ++j) {
           if (planets[j]->diameter > planets[j + 1]->diameter) {
               Planet* temp = planets[j];
               planets[j] = planets[j + 1];
               planets[j + 1] = temp;
           }
       }
   }
}

void SortPlanetsByLife(Planet** planets, int size) {
   for (int i = 0; i < size - 1; ++i) {
       for (int j = 0; j < size - i - 1; ++j) {
           if (planets[j]->hasLife < planets[j + 1]->hasLife) {
               Planet* temp = planets[j];
               planets[j] = planets[j + 1];
               planets[j + 1] = temp;
           }
       }
   }
}

void SortPlanetsBySatellites(Planet** planets, int size) {
   for (int i = 0; i < size - 1; ++i) {
       for (int j = 0; j < size - i - 1; ++j) {
           if (planets[j]->numSatellites > planets[j + 1]->numSatellites) {
               Planet* temp = planets[j];
               planets[j] = planets[j + 1];
               planets[j + 1] = temp;
           }
       }
   }
}

void EditPlanet(Planet** planets, int size, const char* name) {
   for (int i = 0; i < size; ++i) {
       if (std::strcmp(planets[i]->name, name) == 0) {
           std::cout << "Введите новый диаметр: ";
           std::cin >> planets[i]->diameter;
           std::cout << "Есть ли жизнь на планете? (1 - Да, 0 - Нет): ";
           std::cin >> planets[i]->hasLife;
           std::cout << "Введите количество спутников: ";
           std::cin >> planets[i]->numSatellites;
           std::cout << "Планета успешно отредактирована." << std::endl;
           return;
       }
   }

   std::cout << "Планета не найдена." << std::endl;
}

void LoadPlanetsFromFile(Planet**& planets, int& size, const char* filename) {
    char fullPath[256] = "../";
    std::strcat(fullPath, filename);

    std::ifstream file(fullPath);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << fullPath << std::endl;
        return;
    }

    while (!file.eof()) {
        char name_buf[100];
        double diameter;
        bool hasLife;
        int numSatellites;

        file >> name_buf >> diameter >> hasLife >> numSatellites;

        if (!file.fail()) {
            Planet** newPlanets = new Planet*[size + 1];
            for (int i = 0; i < size; ++i) {
                newPlanets[i] = planets[i];
            }
            delete[] planets;
            planets = newPlanets;

            Planet* planet = new Planet;
            int len = strlen(name_buf);
            planet->name = new char[len + 1];
            strcpy(planet->name, name_buf);
            planet->diameter = diameter;
            planet->hasLife = hasLife;
            planet->numSatellites = numSatellites;
            planets[size] = planet;
            size++;
        }
	}

	file.close();
}

void SavePlanetsToFile(Planet** planets, int size, const char* filename) {
    char fullPath[256] = "../";
    std::strcat(fullPath, filename);

    std::ofstream file(fullPath);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << fullPath << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << planets[i]->name << " " << planets[i]->diameter << " "
             << planets[i]->hasLife << " " << planets[i]->numSatellites << std::endl;
    }

    file.close();
    std::cout << "Таблица планет сохранена в файл: " << fullPath << std::endl;
}

void PrintPlanetTable(Planet** planets, int size){
	std :: cout<<"------------------------------------------------------------------"<<std :: endl ;
	std :: cout<<"| "<<std :: setw(12 )<<"Имя"<<"| "<<std :: setw(10 )<<"Диаметр"<<"| "<<std :: setw(7 )<<"Жизнь"<<"| "<<std :: setw(9 )<<"Спутники"<<" |"<<std :: endl ;
	std :: cout<<"------------------------------------------------------------------"<<std :: endl ;

	for(int	i=0;i<size;++i){
		std :: cout<<"| "<<std :: setw(12 )<<planets[i]->name<<"| "<<std :: setw(10 )<<planets[i]->diameter<<"| "<<std :: setw(7 )<<(planets[i]->hasLife ? "Да" : "Нет")<<"| "<<std :: setw(9 )<<planets[i]->numSatellites<<" |"<<std :: endl ;
	}

	std :: cout<<"------------------------------------------------------------------"<<std :: endl ;
}
