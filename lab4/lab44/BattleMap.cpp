#include <iostream>
#include "BattleMap.h"
#include "Ship.h"
#include "ShipManager.h"
#include "Check.h"
#include "AbilityManager.h"
#define _HAS_STD_BYTE 0

using namespace std;

BattleMap::BattleMap(int width, int height) : width(width), height(height) {
    if (width <= 0 || height <= 0) {
        throw invalid_argument("Длинна и ширина должны быть положительными.");
    }
    map.resize(height, vector<CellStatus>(width, CellStatus::Unknown));
    abilityManager = new AbilityManager();
}

bool BattleMap::placeShip(const Ship& ship, int x, int y) {
    // Проверка на пересечение с другими кораблями
    bool canPlace = true; // Логика проверки пересечения
    Check::checkShipPlacement(canPlace);
    if (ship.isVerticalOrientation()) {
        if (y + ship.getLength() > height) return false;
        for (int i = -1; i <= ship.getLength(); ++i) {
            for (int j = -1; j <= 1; ++j) {
                int ny = y + i;
                int nx = x + j;
                if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != CellStatus::Unknown) {
                    return false; // Проверка на занятость соседних клеток
                }
            }
        }
        for (int i = 0; i < ship.getLength(); ++i) {
            map[y + i][x] = CellStatus::Ship; // Размещение корабля
        }
    } else {
        if (x + ship.getLength() > width) return false; // Проверка выхода за границы
        for (int i = -1; i <= ship.getLength(); ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i;
                int ny = y + j;
                if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != CellStatus::Unknown) {
                    return false; // Проверка на занятость соседних клеток
                }
            }
        }
        for (int i = 0; i < ship.getLength(); ++i) {
            map[y][x + i] = CellStatus::Ship; // Размещение корабля
        }
    }
    return true;
}

bool BattleMap::shoot(int x, int y, ShootType shootType) {
    std::string msgHit = shootType == ShootType::Default ? "hit" : "doube damage!!!";
    if (map[y][x] == CellStatus::Ship) {
        map[y][x] = CellStatus::Hit; // Маркируем попадание
        cout << msgHit << endl;
        return true; // Попадание
    } else if (map[y][x] == CellStatus::Unknown) {
        map[y][x] = CellStatus::Miss;  // Маркируем как промах
        cout << "Промах!" << endl;
    }
    return false; // Промах
}

bool BattleMap::isShipDestroyed(int x, int y) {
    vector<std::pair<int, int>> shipCoords = getShipCoordinates(x, y);

    for (const auto& coord : shipCoords) {
        if (map[coord.second][coord.first] == CellStatus::Ship) {
            return false; // Корабль не уничтожен
        }
    }

    markSurroundingCells(x, y);
    return true; // Корабль полностью уничтожен
}

void BattleMap::markSurroundingCells(int x, int y) {
    vector<std::pair<int, int>> shipCoords = getShipCoordinates(x, y);

    // Обводим клетки вокруг всего корабля
    for (const auto& coord : shipCoords) {
        int shipX = coord.first;
        int shipY = coord.second;

        // Обводим клетки вокруг каждого сегмента корабля
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = shipX + dx;
                int ny = shipY + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && map[ny][nx] == CellStatus::Unknown) {
                    map[ny][nx] = CellStatus::Destroyed; // Помечаем клетки как уничтоженные вокруг корабля
                }
            }
        }
    }
}

vector<pair<int, int>> BattleMap::getShipCoordinates(int x, int y) {
    std::vector<std::pair<int, int>> shipCoordinates;

    // Проверяем сегменты корабля в вертикальном направлении
    int ny = y;
    while (ny >= 0 && (map[ny][x] == CellStatus::Ship || map[ny][x] == CellStatus::Hit)) {
        shipCoordinates.push_back({x, ny});
        ny--;
    }
    ny = y + 1;
    while (ny < height && (map[ny][x] == CellStatus::Ship || map[ny][x] == CellStatus::Hit)) {
        shipCoordinates.push_back({x, ny});
        ny++;
    }

    // Проверяем сегменты корабля в горизонтальном направлении
    int nx = x;
    while (nx >= 0 && (map[y][nx] == CellStatus::Ship || map[y][nx] == CellStatus::Hit)) {
        shipCoordinates.push_back({nx, y});
        nx--;
    }
    nx = x + 1;
    while (nx < width && (map[y][nx] == CellStatus::Ship || map[y][nx] == CellStatus::Hit)) {
        shipCoordinates.push_back({nx, y});
        nx++;
    }

    return shipCoordinates;
}

bool BattleMap::allShipsDestroyed() {
    // Проходим по всей карте и ищем клетки с кораблями
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == CellStatus::Ship) {
                return false; // Если находим клетку с кораблем, возвращаем false
            }
        }
    }
    return true; // Все корабли уничтожены
}

int BattleMap::getWidth() const { return width; }
int BattleMap::getHeight() const { return height; }

// Перегрузка оператора вывода для BattleMap
ostream& operator<<(ostream& os, const BattleMap& battleMap) {
    // Сначала записываем размер карты (ширину и высоту)
    os << battleMap.getWidth() << " " << battleMap.getHeight() << std::endl;

    // Далее записываем состояние каждой клетки карты
    for (int i = 0; i < battleMap.getHeight(); ++i) {
        for (int j = 0; j < battleMap.getWidth(); ++j) {
            os << static_cast<int>(battleMap.map[i][j]) << " ";  // Преобразуем CellStatus в int
        }
        os << std::endl;
    }

    return os;
}

// Перегрузка оператора ввода для BattleMap
istream& operator>>(istream& is, BattleMap& battleMap) {
    // Считываем размеры карты
    int width, height;
    is >> width >> height;

    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Размеры карты должны быть положительными.");
    }

    battleMap.width = width;
    battleMap.height = height;

    // Перезагружаем состояние карты
    battleMap.map.resize(height, vector<BattleMap::CellStatus>(width, BattleMap::CellStatus::Unknown));

    // Считываем клетки карты
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int cellStatusInt;
            is >> cellStatusInt;
            battleMap.map[i][j] = static_cast<BattleMap::CellStatus>(cellStatusInt);
        }
    }

    return is;
}
