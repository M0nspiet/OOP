#include "Ability.h"
#include "BattleMap.h"
#include <iostream>

using namespace std;

void DoubleDamageAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    
    cout << "Применена способность: Двойной урон!" << endl;

    int x, y;
    cout << "Введите координаты для атаки (x y): ";
    cin >> x >> y;

    if (botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
        cout << "Попадание! Наносится двойной урон." << endl;
        botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager); // Наносим второй удар
    } else {
        cout << "Промах!" << endl;
    }
}

void ScannerAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    cout << "Применена способность: Сканер!" << endl;

    int x, y;
    cout << "Введите координаты верхнего левого угла области 2x2 для сканирования (x y): ";
    cin >> x >> y;

    if (x + 1 < botMap.getWidth() && y + 1 < botMap.getHeight()) {
        bool foundShip = false;
        for (int dx = 0; dx <= 1; ++dx) {
            for (int dy = 0; dy <= 1; ++dy) {
                if (botMap.map[y + dy][x + dx] == BattleMap::CellStatus::Ship) {
                    foundShip = true;
                    break;
                }
            }
            if (foundShip) break;
        }
        if (foundShip) {
            cout << "Обнаружен корабль в области 2x2!" << endl;
        } else {
            cout << "Корабль в этой области не найден." << endl;
        }
    } else {
        cout << "Ошибка: область выходит за границы поля!" << endl;
    }
}

void BombardmentAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    cout << "Применена способность: Обстрел!" << endl;

    int randomShipIndex = rand() % botShipManager.getShips().size();
    const Ship& randomShip = botShipManager.getShips()[randomShipIndex];
    int segmentIndex = rand() % randomShip.getLength();

    int x = randomShip.getX();
    int y = randomShip.getY();

    // Используем метод isVerticalOrientation() для проверки ориентации
    if (randomShip.isVerticalOrientation()) {
        y += segmentIndex;  // Если корабль вертикальный, меняем только y
    } else {
        x += segmentIndex;  // Если горизонтальный, меняем только x
    }

    // Ограничиваем координаты x и y в пределах от 0 до 9
    x = std::min(std::max(x, 0), 9);
    y = std::min(std::max(y, 0), 9);

    cout << "Обстрел по кораблю с координатами: (" << x << ", " << y << ")" << endl;

    // Проверяем, что координаты не выходят за границы карты
    if (x >= 0 && x < botMap.getWidth() && y >= 0 && y < botMap.getHeight()) {
        botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager); // Выстрел по случайным координатам
    } else {
        cout << "Ошибка: выстрел выходит за пределы карты!" << endl;
    }
}