#include "Ability.h"
#include "BattleMap.h"
#include <iostream>
#include "Check.h"
#include <limits>

using namespace std;

void DoubleDamageAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    cout << "Применена способность: Двойной урон!" << endl;

    int x, y;
    while (true) {
        cout << "Введите координаты для атаки (x y): ";

        // Проверка, что введены именно числа
        if (!(cin >> x >> y)) {
            // Очистка потока ввода
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите два целых числа." << endl;
            continue; // Запросить ввод снова
        }

        // Проверка координат на выход за пределы поля
        try {
            Check::checkAttackBounds(x, y, botMap.getWidth(), botMap.getHeight());
        } catch (const OutOfBoundsAttackException& e) {
            cout << e.what() << endl;
            continue; // Запросить ввод снова
        }

        break; // Выход из цикла, если координаты валидны
    }

    // Совершаем первый выстрел
    if (botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
        cout << "Попадание! Наносится двойной урон." << endl;
        // Совершаем второй выстрел
        botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager); 
    } else {
        cout << "Промах!" << endl;
    }
}

void ScannerAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    cout << "Применена способность: Сканер!" << endl;

    int x, y;
    while (true) {
        cout << "Введите координаты верхнего левого угла области 2x2 для сканирования (x y): ";

        // Проверка, что введены именно числа
        if (!(cin >> x >> y)) {
            // Очистка потока ввода
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите два целых числа." << endl;
            continue; // Запросить ввод снова
        }

        // Проверка, что область 2x2 не выходит за границы поля
        if (x + 1 < botMap.getWidth() && y + 1 < botMap.getHeight()) {
            break; // Ввод успешен, выходим из цикла
        } else {
            cout << "Ошибка: область выходит за границы поля!" << endl;
            continue; // Запросить ввод снова
        }
    }

    // Обрабатываем сканирование области 2x2
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
}

void BombardmentAbility::apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    cout << "Применена способность: Обстрел!" << endl;

    if (botShipManager.getShipCount() == 0) {
        cout << "У противника нет кораблей для обстрела." << endl;
        return;
    }

    // Выбираем случайный корабль
    int randomShipIndex = rand() % botShipManager.getShipCount();
    Ship& randomShip = botShipManager.getShip(randomShipIndex);

    // Проверяем, что корабль не уничтожен
    if (!randomShip.isDestroyed() && randomShip.hitRandomSegment()) {
        cout << "Обстрел по сегменту корабля удался!" << endl;
    } else {
        cout << "Все сегменты корабля уже уничтожены или обстрел не удался!" << endl;
    }
}
