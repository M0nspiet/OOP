#include <windows.h> // РУСИФИКАЦИЯ
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "BattleMap.h"
#include "ShipManager.h"
#include "Bot.h"
#include "Ability.h"
#include "AbilityManager.h"

using namespace std;

int main() {
    // РУСИФИКАЦИЯ
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(static_cast<unsigned int>(time(0))); // Генератор случайных чисел
    int width = 10, height = 10;

    // Инициализация карт и объектов
    BattleMap playerMap(width, height);
    ShipManager playerShipManager;
    BattleMap botMap(width, height);
    ShipManager botShipManager;
    Bot bot(botMap, botShipManager);

    // Инициализация способностей
    AbilityManager abilityManager;
    abilityManager.addAbility(new DoubleDamageAbility());
    abilityManager.addAbility(new ScannerAbility());
    abilityManager.addAbility(new BombardmentAbility());

    // Размещение кораблей
    cout << "Я разместил корабли рандомно." << endl;
    playerShipManager.placeShipsRandomly(playerMap);

    cout << "Бот разместил корабли." << endl;
    botShipManager.placeShipsRandomly(botMap);

    // Игра начинается
    bool player1Turn = true;
    while (true) {
        playerMap.displayDouble(playerMap, botMap, true); // Отображение поля

        if (player1Turn) {
            cout << "Ваш ход:" << endl;

            // Запрос на использование способности
            char useAbility;
            while (true) {
                cout << "Хотите использовать способность? (Y/N): ";
                cin >> useAbility;

                // Проверка корректности ввода
                if (cin.fail() || (toupper(useAbility) != 'Y' && toupper(useAbility) != 'N')) {
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
                    cout << "Некорректный ввод! Попробуйте снова." << endl;
                    continue;
                }

                break;
            }

            if (toupper(useAbility) == 'Y') {
                // Применение случайной способности
                if (abilityManager.getAbilityCount() > 0) {
                    abilityManager.applyRandomAbility(playerMap, botMap, playerShipManager, botShipManager);
                    player1Turn = false; // Ход переходит к боту после использования способности
                } else {
                    std::cout << "Нет доступных способностей для использования." << std::endl;
                }
            }

            // Если способность не использовалась или была отменена, выполняется выстрел
            if (player1Turn) {
                int x, y;
                while (true) {
                    cout << "Введите координаты для атаки (x y): ";
                    if (!(cin >> x >> y)) {
                        cout << "Ошибка ввода! Пожалуйста, введите два целых числа." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (x < 0 || x >= botMap.getWidth() || y < 0 || y >= botMap.getHeight()) {
                        cout << "Координаты вне диапазона! Попробуйте снова." << endl;
                        continue;
                    }
                    break;
                }

                if (!botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
                    player1Turn = false; // Ход переходит к боту при промахе
                }
            }

        } else {
            cout << "Бот делает ход:" << endl;
            auto [x, y] = bot.makeMove();
            cout << "Бот выбрал координаты (" << x << ", " << y << ")" << endl;

            if (!playerMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
                player1Turn = true; // Ход переходит к игроку при промахе
            }
        }

        // Применение случайной способности после уничтожения всех кораблей у бота
        if (botMap.allShipsDestroyed()) {
            cout << "Вы выиграли!" << endl;
            cout << "Применяется случайная способность!" << endl;
            abilityManager.applyRandomAbility(playerMap, botMap, playerShipManager, botShipManager);
            break; // Выход из игры, так как победа достигнута
        } else if (playerMap.allShipsDestroyed()) {
            cout << "О нет, бот победил!" << endl;
            break; // Выход из игры, так как бот победил
        }
    }

    return 0;
}
