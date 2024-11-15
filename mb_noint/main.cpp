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
                if (cin.fail()) {
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
                    cout << "Ошибка ввода! Попробуйте снова." << endl;
                    continue;
                }

                useAbility = toupper(useAbility);
                if (useAbility == 'Y' || useAbility == 'N') break;
                else {
                    cout << "Пожалуйста, введите 'Y' для использования способности или 'N' для пропуска." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера перед повторным запросом
                }
            }

            if (useAbility == 'Y') {
                // Показать доступные способности
                abilityManager.displayAbilities();

                int abilityChoice;
                while (true) {
                    cout << "Введите номер способности, которую хотите использовать (0 для отмены): ";
                    if (!(cin >> abilityChoice)) {
                        cout << "Ошибка ввода! Пожалуйста, введите номер способности." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    // Проверка на корректность выбора способности
                    if (abilityChoice == 0) {
                        cout << "Отмена использования способности." << endl;
                        break;
                    } else if (abilityChoice > 0 && abilityChoice <= abilityManager.getAbilityCount()) {
                        abilityManager.applyAbility(abilityChoice, playerMap, botMap, playerShipManager, botShipManager);
                        player1Turn = false; // Ход переходит к боту после использования способности
                        break;
                    } else {
                        cout << "Некорректный выбор способности! Попробуйте снова." << endl;
                    }
                }
            }

            // Если игрок не использовал способность, он стреляет
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
                    player1Turn = false; // Ход переходит к боту, если промах
                }
            }

        } else {
            cout << "Бот делает ход:" << endl;
            auto [x, y] = bot.makeMove();
            cout << "Бот выбрал координаты (" << x << ", " << y << ")" << endl;

            if (!playerMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
                player1Turn = true; // Ход переходит к игроку
            }
        }

        // Проверка на окончание игры
        if (botMap.allShipsDestroyed()) {
            cout << "Вы выиграли!" << endl;
            break;
        } else if (playerMap.allShipsDestroyed()) {
            cout << "О нет, бот победил!" << endl;
            break;
        }
    }

    return 0;
}
