#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <iostream>

enum Tariff { DEFAULT, SUPER };

class Subscriber {
private:
    char* name;
    int age;
    double balance;
    Tariff tariff;

    void copyFrom(const Subscriber& other);
    void cleanup();

public:
    Subscriber();
    Subscriber(const char* name, int age, double balance, Tariff tariff);
    Subscriber(const Subscriber& other);
    ~Subscriber();

    Subscriber& operator=(const Subscriber& other);

    friend std::ostream& operator<<(std::ostream& os, const Subscriber& subscriber);
    friend std::istream& operator>>(std::istream& is, Subscriber& subscriber);

    static void readFromFile(Subscriber*& subscribers, int& size);
    static void writeToFile(const Subscriber* subscribers, int size);
    static void sortSubscribers(Subscriber* subscribers, int size, int sortBy, bool descending);
    static void addSubscriber(Subscriber*& subscribers, int& size, const Subscriber& newSubscriber);
    static void removeSubscriber(Subscriber*& subscribers, int& size, const char* subscriberName);
    static void editSubscriberByName(Subscriber* subscribers, int size, const char* subscriberName);
    static void displaySubscribers(const Subscriber* subscribers, int size);
};

#endif
