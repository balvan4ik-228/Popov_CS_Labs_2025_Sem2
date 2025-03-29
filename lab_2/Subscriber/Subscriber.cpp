#include "Subscriber.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cstring>
#include <sstream>

Subscriber::Subscriber() : name(nullptr), age(0), balance(0.0), tariff(DEFAULT) {}

Subscriber::Subscriber(const char* name, int age, double balance, Tariff tariff)
    : age(age), balance(balance), tariff(tariff) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Subscriber::Subscriber(const Subscriber& other) : name(nullptr) {
    copyFrom(other);
}

Subscriber::~Subscriber() {
    cleanup();
}

Subscriber& Subscriber::operator=(const Subscriber& other) {
    if(this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

void Subscriber::copyFrom(const Subscriber& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    age = other.age;
    balance = other.balance;
    tariff = other.tariff;
}

void Subscriber::cleanup() {
    delete[] name;
    name = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Subscriber& subscriber) {
    os << std::left
       << subscriber.name << " "
       << subscriber.age << " "
       << subscriber.balance << " "
       << (subscriber.tariff == DEFAULT ? "Default" : "Super");
    return os;
}

std::istream& operator>>(std::istream& is, Subscriber& subscriber) {
    char name[100];
    int age;
    double balance;
    int tariffChoice;

    std::cout << "\n=== Ввод данных абонента ===\n";
    std::cout << "Имя: ";
    is.ignore();
    is.getline(name, 100);

    std::cout << "Возраст: ";
    is >> age;

    std::cout << "Баланс: ";
    is >> balance;

    std::cout << "Тариф (1 - Default, 2 - Super): ";
    is >> tariffChoice;
    while(tariffChoice != 1 && tariffChoice != 2) {
        std::cout << "Неверный ввод! Введите 1 или 2: ";
        is >> tariffChoice;
    }

    delete[] subscriber.name;
    subscriber.name = new char[strlen(name) + 1];
    strcpy(subscriber.name, name);
    subscriber.age = age;
    subscriber.balance = balance;
    subscriber.tariff = (tariffChoice == 1) ? DEFAULT : SUPER;

    return is;
}

void Subscriber::readFromFile(Subscriber*& subscribers, int& size) {
    const char* filename = "Subscribers.txt";
    std::ifstream file(filename);
    if(!file) {
        std::cerr << "Ошибка открытия файла " << filename << "\n";
        return;
    }

    Subscriber temp[100];
    int count = 0;
    std::string line;

    while(std::getline(file, line) && count < 100) {
        std::istringstream iss(line);
        std::string name;
        int age;
        double balance;
        std::string tariffStr;

        if(iss >> name >> age >> balance >> tariffStr) {
            Tariff tariff = (tariffStr == "Super") ? SUPER : DEFAULT;
            temp[count++] = Subscriber(name.c_str(), age, balance, tariff);
        }
    }

    if(count > 0) {
        delete[] subscribers;
        subscribers = new Subscriber[count];
        for(int i = 0; i < count; ++i) {
            subscribers[i] = temp[i];
        }
        size = count;
    }
    file.close();
}

void Subscriber::writeToFile(const Subscriber* subscribers, int size) {
    const char* filename = "Subscribers.txt";
    std::ofstream file(filename);
    if(!file) {
        std::cerr << "Ошибка создания файла " << filename << "\n";
        return;
    }

    for(int i = 0; i < size; ++i) {
        file << subscribers[i].name << " "
             << subscribers[i].age << " "
             << std::fixed << std::setprecision(2) << subscribers[i].balance << " "
             << (subscribers[i].tariff == DEFAULT ? "Default" : "Super") << "\n";
    }
    file.close();
}

void Subscriber::sortSubscribers(Subscriber* subscribers, int size, int sortBy, bool descending) {
    auto compare = [sortBy, descending](const Subscriber& a, const Subscriber& b) {
        switch(sortBy) {
            case 1: return descending ? strcmp(a.name, b.name) > 0 : strcmp(a.name, b.name) < 0;
            case 2: return descending ? a.age > b.age : a.age < b.age;
            case 3: return descending ? a.balance > b.balance : a.balance < b.balance;
            case 4: return descending ? a.tariff > b.tariff : a.tariff < b.tariff;
            default: return false;
        }
    };
    std::sort(subscribers, subscribers + size, compare);
}

void Subscriber::addSubscriber(Subscriber*& subscribers, int& size, const Subscriber& newSubscriber) {
    if(size >= 100) {
        std::cout << "Достигнут лимит в 100 абонентов!\n";
        return;
    }
    Subscriber* newArray = new Subscriber[size + 1];
    for(int i = 0; i < size; ++i) {
        newArray[i] = subscribers[i];
    }
    newArray[size] = newSubscriber;
    delete[] subscribers;
    subscribers = newArray;
    ++size;
}

void Subscriber::removeSubscriber(Subscriber*& subscribers, int& size, const char* subscriberName) {
    bool found = false;
    for(int i = 0; i < size; ++i) {
        if(strcmp(subscribers[i].name, subscriberName) == 0) {
            found = true;
            for(int j = i; j < size - 1; ++j) {
                subscribers[j] = subscribers[j + 1];
            }
            --size;
            break;
        }
    }

    if(!found) {
        std::cout << "Абонент '" << subscriberName << "' не найден!\n";
        return;
    }

    Subscriber* newArray = new Subscriber[size];
    for(int i = 0; i < size; ++i) {
        newArray[i] = subscribers[i];
    }
    delete[] subscribers;
    subscribers = newArray;
}

void Subscriber::editSubscriberByName(Subscriber* subscribers, int size, const char* subscriberName) {
    bool found = false;
    for(int i = 0; i < size; ++i) {
        if(strcmp(subscribers[i].name, subscriberName) == 0) {
            found = true;
            std::cout << "Текущие данные абонента:\n";
            displaySubscribers(&subscribers[i], 1);
            std::cout << "Введите новые данные:\n";
            std::cin >> subscribers[i];
            break;
        }
    }

    if(!found) {
        std::cout << "Абонент '" << subscriberName << "' не найден!\n";
    }
}

void Subscriber::displaySubscribers(const Subscriber* subscribers, int size) {
    if(size == 0) {
        std::cout << "Список планет пуст!\n";
        return;
    }

    std::cout << "\n" << std::string(65, '=') << "\n";
    std::cout << std::left
              << std::setw(18) << "Имя"
              << std::setw(22) << "Возраст"
              << std::setw(23) << "Баланс"
              << std::setw(10) << "Тариф"
              << "\n";
    std::cout << std::string(65, '-') << "\n";

    for(int i = 0; i < size; ++i) {
        std::cout <<std::left
                  << std::setw(23) << subscribers[i].name
                  << std::setw(15) << subscribers[i].age
                  << std::setw(15) << subscribers[i].balance
                  << std::setw(10) << (subscribers[i].tariff == DEFAULT ? "Default" : "Super")
                  << "\n";
    }

    std::cout << std::string(65, '=') << "\n";
}
