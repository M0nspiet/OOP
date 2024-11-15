#include "ShipManager.h"
#include "BattleMap.h"
#include <cstdlib>
//Долден принимать вектор кораблей
ShipManager::ShipManager() {
    vector<int> sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // дефолт кораблики
    for (int size : sizes) {
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
