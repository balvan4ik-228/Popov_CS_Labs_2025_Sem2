#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <cstring>

class Planet {
private:
    char* name;
    long long diameter;
    int satellites;
    bool hasLife;

    void copyFrom(const Planet& other);
    void cleanup();

public:
    Planet();
    Planet(const char* name, long long diameter, int satellites, bool hasLife);
    Planet(const Planet& other);
    ~Planet();

    Planet& operator=(const Planet& other);
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& is, Planet& planet);

    const char* getName() const { return name; }
    long long getDiameter() const { return diameter; }
    int getSatellites() const { return satellites; }
    bool getHasLife() const { return hasLife; }

    static void readFromFile(Planet*& planets, int& size);
    static void writeToFile(const Planet* planets, int size);
    static void sortPlanets(Planet* planets, int size, int sortBy, bool descending);
    static void addPlanet(Planet*& planets, int& size, const Planet& newPlanet);
    static void removePlanet(Planet*& planets, int& size, const char* planetName);
    static void editPlanetByName(Planet* planets, int size, const char* planetName);
    static void displayPlanets(const Planet* planets, int size);
};

#endif
