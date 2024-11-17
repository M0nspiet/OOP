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
#include "Check.h"

using namespace std;

int main() {
    // РУСИФИКАЦИЯ
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    int width = 10, height = 10;

    // Инициализация карт и объектов
    BattleMap playerMap(width, height);
    ShipManager playerShipManager;
    BattleMap botMap(width, height);
    ShipManager botShipManager;
    Bot bot(botMap, botShipManager);

    // Инициализация способностей
    AbilityManager abilityManager;
    abilityManager.addAbility(new BombardmentAbility());
    abilityManager.addAbility(new DoubleDamageAbility());
    abilityManager.addAbility(new ScannerAbility());
    abilityManager.assignRandomAbility();

    // Размещение кораблей
    cout << "Я разместил корабли рандомно." << endl;
    playerShipManager.placeShipsRandomly(playerMap);

    cout << "Бот разместил корабли." << endl;
    botShipManager.placeShipsRandomly(botMap);

    // Начало игрового процесса
    bool player1Turn = true;
    while (true) {
        playerMap.displayDouble(playerMap, botMap, true); // Отображение поля

        try {
            if (player1Turn) {
                cout << "Ваш ход:" << endl;

                // Использование способности
                char useAbility;
                while (true) {
                    cout << "Хотите использовать способность? (Y/N): ";
                    cin >> useAbility;

                    // Проверка корректности ввода
                    if (cin.fail() || (toupper(useAbility) != 'Y' && toupper(useAbility) != 'N')) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Некорректный ввод! Попробуйте снова." << endl;
                        continue;
                    }
                    break;
                }

                if (toupper(useAbility) == 'Y') {
                    // Проверка, есть ли доступные способности
                    Check::checkAbility(abilityManager.hasAnyAbility());

                    // В цикле выбор способности
                    while (true) {
                        cout << "Доступные способности:" << endl;
                        abilityManager.displayAbilities(); // Показываем список способностей
                        cout << "Введите номер способности (0 для отмены): ";
                        int abilityChoice;
                        cin >> abilityChoice;

                        // Обработка выхода из выбора
                        if (abilityChoice == 0) {
                            cout << "Выход из меню выбора способностей." << endl;
                            break;
                        }

                        // Применение выбранной способности
                        if (abilityManager.isValidAbilityChoice(abilityChoice)) {
                            abilityManager.applyAbility(abilityChoice, playerMap, botMap, playerShipManager, botShipManager);
                            player1Turn = false; // Ход переходит к боту после использования способности
                            break;
                        } else {
                            cout << "Некорректный выбор способности! Попробуйте снова." << endl;
                        }
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

                        // Проверка, что координаты в пределах карты
                        try {
                            Check::checkAttackBounds(x, y, botMap.getWidth(), botMap.getHeight());
                        } catch (const OutOfBoundsAttackException& e) {
                            cout << e.what() << endl;
                            continue; // Запросить ввод снова
                        }
                        break;
                    }

                    // Атака по координатам
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

            // Проверка победы
            if (botMap.allShipsDestroyed()) {
                cout << "Вы выиграли!" << endl;
                cout << "Применяется случайная способность!" << endl;
                abilityManager.applyRandomAbility(playerMap, botMap, playerShipManager, botShipManager);
                break;
            } else if (playerMap.allShipsDestroyed()) {
                cout << "О нет, бот победил!" << endl;
                break;
            }

        } catch (const GameException& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    return 0;
}
