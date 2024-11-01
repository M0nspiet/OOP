#include "ShipManager.h"
#include <cstdlib>
#include <limits>
//Долден принимать вектор кораблей
ShipManager::ShipManager() {
    createShips();
    // vector<int> sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // дефолт кораблики
    // for (int size : sizes) {
    //     ships.emplace_back(size, rand() % 2); // Случайная ориентация (вертикально/горизонтально)
    // }
}

void ShipManager::createShips() {
    int numberOfShips;

    do {
        cout << "Введите количество кораблей (максимум 10): ";
        cin >> numberOfShips;

        if (cin.fail() || numberOfShips < 1 || numberOfShips > 10) {
            cin.clear(); // Очистка флага ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорировать неправильный ввод
            cout << "Ошибка: введите число от 1 до 10." << endl;
        } else {
            break; // Выход из цикла, если ввод корректен
        }
    } while (true);

    ships.reserve(numberOfShips);

    for (int i = 0; i < numberOfShips; ++i) {
        int size;

        do {
            cout << "Введите размер корабля #" << (i + 1) << " (максимум 4): ";
            cin >> size;

            if (cin.fail() || size < 1 || size > 4) {
                cin.clear(); // Очистка флага ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорировать неправильный ввод
                cout << "Ошибка: введите число от 1 до 4." << endl;
            } else {
                break; // Выход из цикла, если ввод корректен
            }
        } while (true);

        ships.emplace_back(size, rand() % 2); // Случайная ориентация (вертикально/горизонтально)
    }
}

const vector<Ship>& ShipManager::getShips() const {
    return ships;
}

void ShipManager::placeShipsRandomly(BattleMap& battleMap) {
    for (const Ship& ship : ships) {
        bool placed = false;
        while (!placed) {
            int x = rand() % battleMap.getWidth();
            int y = rand() % battleMap.getHeight();
            bool isVertical = rand() % 2;

            Ship randomShip(ship.getLength(), isVertical);
            placed = battleMap.placeShip(randomShip, x, y);
        }
    }
}
