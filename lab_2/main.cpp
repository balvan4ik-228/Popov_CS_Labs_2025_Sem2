#include "Subscriber/Subscriber.h"
#include "Planet/Planet.h"
#include <iostream>
#include <limits>

void displayMainMenu() {
    std::cout << "\n=== Главное меню ==="
              << "\n1. Работа с абонентами"
              << "\n2. Работа с планетами"
              << "\n0. Выход"
              << "\nВыберите режим: ";
}

void displayAbonentMenu() {
    std::cout << "\n=== Меню абонентов ==="
              << "\n1. Загрузить из файла"
              << "\n2. Добавить абонента"
              << "\n3. Удалить абонента"
              << "\n4. Сортировать абонентов"
              << "\n5. Редактировать абонента"
              << "\n6. Показать всех абонентов"
              << "\n7. Сохранить в файл"
              << "\n0. Назад"
              << "\nВыберите действие: ";
}

void displayPlanetMenu() {
    std::cout << "\n=== Меню планет ==="
              << "\n1. Загрузить из файла"
              << "\n2. Добавить планету"
              << "\n3. Удалить планету"
              << "\n4. Сортировать планеты"
              << "\n5. Редактировать планету"
              << "\n6. Показать все планеты"
              << "\n7. Сохранить в файл"
              << "\n0. Назад"
              << "\nВыберите действие: ";
}

void displaySortOptions(bool isAbonent) {
    if(isAbonent) {
        std::cout << "\nПоля для сортировки:"
                  << "\n1. По имени"
                  << "\n2. По возрасту"
                  << "\n3. По балансу"
                  << "\n4. По тарифу";
    } else {
        std::cout << "\nПоля для сортировки:"
                  << "\n1. По названию"
                  << "\n2. По диаметру"
                  << "\n3. По количеству спутников"
                  << "\n4. По наличию жизни";
    }
    std::cout << "\nВыберите поле: ";
}

void displayOrderOptions() {
    std::cout << "\nНаправление сортировки:"
              << "\n1. По возрастанию"
              << "\n2. По убыванию"
              << "\nВыберите вариант: ";
}

void subscriberOperations() {
    Subscriber* subscribers = nullptr;
    int subscriberCount = 0;
    int choice;

    while(true) {
        std::cout << "\n=== Меню управления абонентами ==="
                  << "\n1. Загрузить из файла"
                  << "\n2. Добавить абонента"
                  << "\n3. Удалить абонента"
                  << "\n4. Сортировать абонентов"
                  << "\n5. Редактировать абонента"
                  << "\n6. Показать всех абонентов"
                  << "\n7. Сохранить в файл"
                  << "\n0. Вернуться в главное меню"
                  << "\nВыберите действие: ";
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        switch(choice) {
            case 1: {
                Subscriber::readFromFile(subscribers, subscriberCount);
                std::cout << "Данные загружены. Всего абонентов: " << subscriberCount << "\n";
                break;
            }
            case 2: {
                if(subscriberCount >= 100) {
                    std::cout << "Достигнут лимит в 100 абонентов!\n";
                    break;
                }
                Subscriber newSubscriber;
                std::cin >> newSubscriber;
                Subscriber::addSubscriber(subscribers, subscriberCount, newSubscriber);
                std::cout << "Абонент добавлен.\n";
                break;
            }
            case 3: {
                if(subscriberCount == 0) {
                    std::cout << "Список абонентов пуст!\n";
                    break;
                }
                Subscriber::displaySubscribers(subscribers, subscriberCount);
                std::cout << "Введите имя абонента для удаления: ";
                char name[100];
                std::cin.ignore();
                std::cin.getline(name, 100);
                Subscriber::removeSubscriber(subscribers, subscriberCount, name);
                break;
            }
            case 4: {
                if(subscriberCount == 0) {
                    std::cout << "Нет данных для сортировки!\n";
                    break;
                }
                std::cout << "\nСортировать по:"
                          << "\n1. Имени"
                          << "\n2. Возрасту"
                          << "\n3. Балансу"
                          << "\n4. Тарифу"
                          << "\nВыберите поле: ";
                int field;
                std::cin >> field;

                if(field < 1 || field > 4) {
                    std::cout << "Неверный выбор!\n";
                    break;
                }

                std::cout << "\nПорядок сортировки:"
                          << "\n1. По возрастанию"
                          << "\n2. По убыванию"
                          << "\nВыберите порядок: ";
                int order;
                std::cin >> order;

                if(order != 1 && order != 2) {
                    std::cout << "Неверный выбор!\n";
                    break;
                }

                Subscriber::sortSubscribers(subscribers, subscriberCount, field, order == 2);
                std::cout << "Сортировка выполнена.\n";
                Subscriber::displaySubscribers(subscribers, subscriberCount);
                break;
            }
            case 5: {
                if(subscriberCount == 0) {
                    std::cout << "Список абонентов пуст!\n";
                    break;
                }
                Subscriber::displaySubscribers(subscribers, subscriberCount);
                std::cout << "Введите имя абонента для редактирования: ";
                char name[100];
                std::cin.ignore();
                std::cin.getline(name, 100);
                Subscriber::editSubscriberByName(subscribers, subscriberCount, name);
                break;
            }
            case 6: {
                Subscriber::displaySubscribers(subscribers, subscriberCount);
                break;
            }
            case 7: {
                Subscriber::writeToFile(subscribers, subscriberCount);
                std::cout << "Данные сохранены в файл.\n";
                break;
            }
            case 0: {
                delete[] subscribers;
                subscribers = nullptr;
                subscriberCount = 0;
                return;
            }
            default: {
                std::cout << "Неверный выбор!\n";
                break;
            }
        }
    }
}

void planetOperations() {
    Planet* planets = nullptr;
    int planetCount = 0;
    int choice;

    while(true) {
        displayPlanetMenu();
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        switch(choice) {
            case 1: {
                Planet::readFromFile(planets, planetCount);
                break;
            }
            case 2: {
                if(planetCount >= 100) {
                    std::cout << "Достигнут лимит в 100 планет!\n";
                    break;
                }
                Planet newPlanet;
                std::cin >> newPlanet;
                Planet::addPlanet(planets, planetCount, newPlanet);
                break;
            }
            case 3: {
                if(planetCount == 0) {
                    std::cout << "Список планет пуст!\n";
                    break;
                }
                Planet::displayPlanets(planets, planetCount);
                std::cout << "Введите название планеты для удаления: ";
                std::string planetName;
                std::cin.ignore();
                std::getline(std::cin, planetName);
                Planet::removePlanet(planets, planetCount, planetName.c_str());
                break;
            }
            case 4: {
                if(planetCount == 0) {
                    std::cout << "Нет данных для сортировки!\n";
                    break;
                }
                int field, order;
                displaySortOptions(false);
                std::cin >> field;
                if(field < 1 || field > 4) break;
                displayOrderOptions();
                std::cin >> order;
                if(order != 1 && order != 2) break;
                Planet::sortPlanets(planets, planetCount, field, order == 2);
                Planet::displayPlanets(planets, planetCount);
                break;
            }
            case 5: {
                if(planetCount == 0) {
                    std::cout << "Список планет пуст!\n";
                    break;
                }
                Planet::displayPlanets(planets, planetCount);
                std::cout << "Введите название планеты для редактирования: ";
                std::string planetName;
                std::cin.ignore();
                std::getline(std::cin, planetName);
                Planet::editPlanetByName(planets, planetCount, planetName.c_str());
                break;
            }
            case 6: {
                Planet::displayPlanets(planets, planetCount);
                break;
            }
            case 7: {
                Planet::writeToFile(planets, planetCount);
                break;
            }
            case 0: {
                delete[] planets;
                return;
            }
            default: {
                std::cout << "Неверный выбор!\n";
                break;
            }
        }
    }
}

int main() {
    int choice;

    while(true) {
        displayMainMenu();
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        switch(choice) {
            case 1:
                subscriberOperations();
                break;
            case 2:
                planetOperations();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Неверный выбор!\n";
        }
    }
}
