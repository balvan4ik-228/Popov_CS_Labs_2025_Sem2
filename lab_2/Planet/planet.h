#ifndef PLANET_H
#define PLANET_H

class Planet {
public:
    char* name;
    double diameter;
    bool hasLife;
    int numSatellites;

    Planet();
    Planet(const char* name, double diameter, bool hasLife, int numSatellites);
    Planet(const Planet& other);
    ~Planet();

    Planet& operator=(const Planet& other);
};

void AddPlanet(Planet**& planets, int& size);
void DeletePlanet(Planet**& planets, int& size, const char* name);
void SortPlanetsByName(Planet** planets, int size);
void SortPlanetsByDiameter(Planet** planets, int size);
void SortPlanetsByLife(Planet** planets, int size);
void SortPlanetsBySatellites(Planet** planets, int size);
void EditPlanet(Planet** planets, int size, const char* name);
void LoadPlanetsFromFile(Planet**& planets, int& size, const char* filename);
void PrintPlanetTable(Planet** planets, int size);
void SavePlanetsToFile(Planet** planets, int size, const char* filename);

#endif
