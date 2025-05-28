#include "Tasks.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <string>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

void Date::print() const {
    printf("%02d.%02d.%04d", day, month, year);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return (day == other.day) && (month == other.month) && (year == other.year);
}

bool Date::isFuture() const {
    std::time_t now = std::time(nullptr);
    std::tm* current = std::localtime(&now);
    Date today(current->tm_mday, current->tm_mon + 1, current->tm_year + 1900);
    return (*this < today) ? false : !(*this == today);
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

void Time::print() const {
    printf("%02d:%02d:%02d", hours, minutes, seconds);
}

bool Time::operator<(const Time& other) const {
    if (hours != other.hours) return hours < other.hours;
    if (minutes != other.minutes) return minutes < other.minutes;
    return seconds < other.seconds;
}

bool Time::operator==(const Time& other) const {
    return (hours == other.hours) && (minutes == other.minutes) && (seconds == other.seconds);
}

bool Time::isNight() const {
    return (hours >= 0) && (hours < 5);
}

void task1() {
    std::string name, patronymic, surname;
    std::cout << "Введите имя: ";
    std::cin >> name;
    std::cout << "Введите отчество: ";
    std::cin >> patronymic;
    std::cout << "Введите фамилию: ";
    std::cin >> surname;

    auto capitalize = [](std::string& word) {
        if (!word.empty()) {
            word[0] = std::toupper(word[0]);
        }
    };

    capitalize(name);
    capitalize(patronymic);
    capitalize(surname);

    std::string initials =
        std::string(1, name[0]) + ". " +
        std::string(1, patronymic[0]) + ". " +
        surname;

    std::cout << "Инициалы: " << initials << "\n";
}

void task2() {
    std::string text;
    std::cout << "Введите текст: ";
    std::cin.ignore();
    getline(std::cin, text);
    size_t first = text.find('a');
    if (first == std::string::npos) {
        std::cout << "Буква 'a' не найдена!\n";
        return;
    }
    size_t second = text.find('a', first + 1);
    std::string result = text.substr(first + 1, second - first);
    std::cout << "Результат: " << result << "\n";
}

void task3() {
    std::ifstream in("../Tasks/task3_1.txt");
    std::ofstream out("../Tasks/task3_2.txt");
    if (!in || !out) {
        std::cerr << "Ошибка открытия файлов!\n";
        return;
    }
    std::string line;
    while (getline(in, line)) {
        size_t pos = 0;
        while ((pos = line.find('.', pos)) != std::string::npos) {
            line.replace(pos, 1, "...");
            pos += 3;
        }
        out << line << "\n";
    }
    std::cout << "Файл обработан успешно!\n";
}

void task4() {
    std::vector<std::string> vec;
    std::string line;
    std::cout << "Введите строки (пустая строка для завершения):\n";
    while (getline(std::cin, line) && !line.empty()) {
        vec.push_back(line);
    }
    printVector(vec);
    if (vec.size() > 3) {
        vec.erase(vec.begin() + 3);
    }
    printVector(vec);
}

void printVector(const std::vector<std::string>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << i << ": " << vec[i] << "\n";
    }
}

void task5() {
    std::vector<Date> dates = {
        Date(1, 2, 1963),
        Date(14, 7, 1995),
        Date(7, 12, 2088),
        Date(5, 3, 2030),
        Date(24, 9, 2013),
        Date(19, 9, 2020)
    };
    printDates(dates);
    std::vector<Date> futureDates;
    for (const auto& d : dates) {
        if (d.isFuture()) {
            futureDates.push_back(d);
        }
    }
    std::cout << "Будущие даты:\n";
    printDates(futureDates);
}

void printDates(const std::vector<Date>& dates) {
    for (const auto& d : dates) {
        d.print();
        std::cout << "\n";
    }
}

void task6() {
    std::list<std::string> lst;
    std::string line;
    std::cout << "Введите строки (пустая строка для завершения):\n";
    while (getline(std::cin, line) && !line.empty()) {
        lst.push_back(line);
    }
    int index = 0;
    for (const auto& s : lst) {
        std::cout << index++ << ": " << s << "\n";
    }
    if (lst.size() > 3) {
        auto it = lst.begin();
        std::advance(it, 3);
        lst.erase(it);
    }
    index = 0;
    for (const auto& s : lst) {
        std::cout << index++ << ": " << s << "\n";
    }
}

void task7() {
    std::list<Time> times = {
        Time(1, 2, 63),
        Time(14, 57, 19),
        Time(7, 32, 20),
        Time(5, 13, 23),
        Time(10, 19, 45),
        Time(19, 9, 59)
    };
    printTimes(times);
    std::list<Time> nightTimes;
    for (const auto& t : times) {
        if (t.isNight()) {
            nightTimes.push_back(t);
        }
    }
    std::cout << "Ночное время:\n";
    printTimes(nightTimes);
}

void printTimes(const std::list<Time>& times) {
    for (const auto& t : times) {
        t.print();
        std::cout << "\n";
    }
}

void task8() {
    std::map<std::string, int> inventory = {
        {"Отвертка", 0},
        {"Молоток", 10},
        {"Гайки", 100},
        {"Профиль", 0},
        {"Уголок", 9},
        {"Доска", 17}
    };
    for (const auto& [item, count] : inventory) {
        if (count != 0) {
            std::cout << item << " - " << count << "\n";
        }
    }
}

void task9() {
    std::map<std::string, int> classes = {
        {"1а", 21}, {"1б", 20}, {"2", 25}, {"3а", 20}, {"3б", 23},
        {"4а", 25}, {"4б", 25}, {"5а", 26}, {"5б", 25}, {"6a", 19},
        {"6б", 18}, {"7а", 26}, {"7б", 25}, {"8", 25}, {"9", 17}, {"10 ", 15}, {"11 ", 14}
    };
    int total = 0;
    for (const auto& [cls, count] : classes) {
        total += count;
        std::cout << cls << ": " << count << "\n";
    }
    std::cout << "Всего учащихся: " << total << "\n";
}
