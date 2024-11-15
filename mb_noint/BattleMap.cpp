#include <iostream>
#include "BattleMap.h"
#include "Ship.h"
#include "ShipManager.h"
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
    if (ship.isVerticalOrientation()) {
        if (y + ship.getLength() > height) return false; // Проверка выхода за границы
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

bool BattleMap::shoot(int x, int y, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (map[y][x] == CellStatus::Ship) {
        map[y][x] = CellStatus::Hit; // Маркируем попадание
        cout << "Попадание!" << endl;

        // Проверяем, уничтожен ли корабль
        if (isShipDestroyed(x, y)) {
            cout << "Корабль уничтожен!" << endl;
            // abilityManager->applyRandomAbility(playerMap, botMap, playerShipManager, botShipManager);
            // Применяем случайную способность
            if (abilityManager) {  // Убедитесь, что abilityManager инициализирован
                abilityManager->applyRandomAbility(playerMap, botMap, playerShipManager, botShipManager);
            }
        }

        return true; // Попадание
    }

    cout << "Промах!" << endl;
    return false; // Промах
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

bool BattleMap::isShipDestroyed(int x, int y) {
    std::vector<std::pair<int, int>> shipCoords = getShipCoordinates(x, y);

    for (const auto& coord : shipCoords) {
        if (map[coord.second][coord.first] == CellStatus::Ship) {
            return false; // Корабль не уничтожен
        }
    }

    return true; // Корабль полностью уничтожен
}

void BattleMap::displayDouble(const BattleMap& playerMap, const BattleMap& botMap, bool hideBotShips) {
    cout << "Поле игрока" << string(22, ' ') << "Поле бота" << endl;

    // Отображение заголовка с номерами столбцов для обоих игроков
    cout << "  "; // Для выравнивания поля 1
    for (int col = 0; col < playerMap.getWidth(); ++col) {
        cout << col << " ";
    }
    cout << string(8, ' '); // Пробел между полями
    cout << "  "; // Для выравнивания поля 2
    for (int col = 0; col < botMap.getWidth(); ++col) {
        cout << col << " ";
    }
    cout << endl;

    // Отображение строк с обеих карт
    for (int row = 0; row < playerMap.getHeight(); ++row) {
        // Вывод строки для поля игрока
        cout << row << " "; // Номер строки
        for (CellStatus cell : playerMap.map[row]) {
            char displayChar;
            switch (cell) {
                case CellStatus::Unknown: displayChar = '.'; break;
                case CellStatus::Empty: displayChar = ' '; break;
                case CellStatus::Ship: displayChar = 'S'; break; // Отображаем корабли игрока
                case CellStatus::Hit: displayChar = 'X'; break; // Отображаем попадания
                case CellStatus::Miss: displayChar = 'O'; break; // Отображаем промахи
                case CellStatus::Destroyed: displayChar = '#'; break; // Уничтоженные корабли
            }
            cout << displayChar << ' ';
        }

        // Пробел между полями
        cout << string(8, ' ');

        // Вывод строки для поля бота
        cout << row << " "; // Номер строки
        for (CellStatus cell : botMap.map[row]) {
            char displayChar;
            switch (cell) {
                case CellStatus::Unknown: displayChar = '.'; break;
                case CellStatus::Empty: displayChar = ' '; break;
                case CellStatus::Ship:
                    if (hideBotShips) {
                        displayChar = '.'; // Скрываем корабли бота
                    } else {
                        displayChar = 'S'; // Показываем корабли бота (для отладки)
                    }
                    break;
                case CellStatus::Hit: displayChar = 'X'; break; // Показываем попадания
                case CellStatus::Miss: displayChar = 'O'; break; // Показываем промахи
                case CellStatus::Destroyed: displayChar = '#'; break; // Уничтоженные корабли
            }
            cout << displayChar << ' ';
        }

        cout << endl;
    }
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

BattleMap::CellStatus BattleMap::getCellStatus(int x, int y) const {
    return map[y][x];
}

void BattleMap::applyDoubleDamage(int x, int y) {
    // Например, если попали по кораблю, сразу уничтожаем сегмент
    if (map[y][x] == CellStatus::Ship) {
        map[y][x] = CellStatus::Hit;
        // Уничтожаем сразу два сегмента, если это возможно
        // Здесь логика зависит от вашей реализации кораблей и их сегментов
        cout << "Двойной урон! Два сегмента уничтожены." << endl;
    }
}

int BattleMap::getWidth() const { return width; }
int BattleMap::getHeight() const { return height; }