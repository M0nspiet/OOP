#include "ShipManager.h"
#include "BattleMap.h"
#include <cstdlib>

ShipManager::ShipManager() {
    initializeShips();  // Инициализация кораблей при создании объекта
}

void ShipManager::initializeShips() {
    ships.clear();  // Очищаем вектор перед инициализацией

    // Список размеров кораблей
    std::vector<int> sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};  // Дефолтные размеры кораблей
    for (int size : sizes) {
        ships.emplace_back(size, rand() % 2);  // Создаем корабли с случайной ориентацией
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

// Перегрузка оператора вывода для ShipManager
ostream& operator<<(ostream& os, const ShipManager& shipManager) {
    os << shipManager.ships.size() << endl;
    for (const auto& ship : shipManager.ships) {
        os << ship << endl;
    }
    return os;
}

// Перегрузка оператора ввода для ShipManager
istream& operator>>(istream& is, ShipManager& shipManager) {
    size_t shipCount;
    is >> shipCount;
    shipManager.ships.clear();  // Очищаем вектор перед добавлением новых кораблей
    shipManager.ships.reserve(shipCount);  // Резервируем место для кораблей

    for (size_t i = 0; i < shipCount; ++i) {
        Ship ship;
        is >> ship;
        shipManager.ships.emplace_back(std::move(ship));  // Добавляем корабль в вектор
    }
    return is;
}