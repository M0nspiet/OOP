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

    int x = randomShip.getX() + segmentIndex;
    int y = randomShip.getY();

    cout << "Обстрел по кораблю " << randomShip.getLength() << "-сегментному и его сегменту " << segmentIndex << endl;

    botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager); // Выстрел по случайным координатам
}
