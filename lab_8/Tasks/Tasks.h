#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <list>
#include <map>
#include <string>

// Задание 5: Класс Date
class Date {
private:
    int day, month, year;
public:
    Date(int d = 1, int m = 1, int y = 1970);
    void print() const;
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool isFuture() const;
};

// Задание 7: Класс Time
class Time {
private:
    int hours, minutes, seconds;
public:
    Time(int h = 0, int m = 0, int s = 0);
    void print() const;
    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;
    bool isNight() const;
};

// Прототипы функций для заданий
void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();

// Вспомогательные функции
void printVector(const std::vector<std::string>& vec);
void printDates(const std::vector<Date>& dates);
void printTimes(const std::list<Time>& times);

#endif
