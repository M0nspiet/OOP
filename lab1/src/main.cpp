#define NOCRYPT //ЧТО БЫ НЕ БЫЛО КОНФЛИКТОВ С bite::
#define _HAS_STD_BYTE 0 //ЧТО воообще не было ошибок
#include <windows.h> //РУСИФИКАЦИЯ
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BattleMap.h"
#include "ShipManager.h"
#include "Bot.h"
#include <limits>

using namespace std;

int main() {
    //РУСИФИКАЦИЯ
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(static_cast<unsigned int>(time(0))); //Генератор рандома на плюсах
    int width = 10, height = 10; 
    
    //Реализация классов
    BattleMap playerMap(width, height);
    ShipManager playerShipManager;
    BattleMap botMap(width, height);
    ShipManager botShipManager;
    Bot bot(botMap, botShipManager);
    
    //Ручками долго
    cout << "Я разместил корабли рандомно." << endl;
    playerShipManager.placeShipsRandomly(playerMap);

    cout << "Бот разместил корабли." << endl;
    botShipManager.placeShipsRandomly(botMap);

    // cout << "Поля после размещения кораблей:" << endl;
    // playerMap.displayDouble(playerMap, botMap, true);

    // Игра начинается
    bool player1Turn = true;
    while (true) {

        playerMap.displayDouble(playerMap, botMap, true); // Рисуем поле на каждом ходе (кроме хода бота)

        if (player1Turn) {
            cout << "Я хожу:" << endl;
            int x = -1, y = -1;

            // Проверка корректности ввода координат
            while (true) {
                cout << "Куда тыкать (x y): ";
                cin >> x >> y;

                if (cin.fail() || x < 0 || x >= width || y < 0 || y >= height) {
                    cin.clear(); // Сбрасываем флаги ошибки
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем входной поток
                    cout << "Ошибка: введите корректные координаты форматом (x y)" << endl;
                } else {
                    break;
                }
            }

            if (!botMap.shoot(x, y)) {
                player1Turn = false;
            }
        } else {
            cout << "Бот тыкает:" << endl;
            auto [x, y] = bot.makeMove(); // Бот мейк мув
            cout << "Бот тыкнул в (" << x << ", " << y << ")" << endl;

            if (!playerMap.shoot(x, y)) {
                player1Turn = true;
            }
        }

        // Завершение игры
        if (botMap.allShipsDestroyed()) {
            cout << "Я выйграл!" << endl;
            break;
        } else if (playerMap.allShipsDestroyed()) {
            cout << "О нет, восстание машин началось !!!" << endl;
            break;
        }
    }
    // while (true) {
        
    //     playerMap.displayDouble(playerMap, botMap, true); // Рисуем поле на каждом ходе (кроме хода бота)

    //     if (player1Turn) {
    //         cout << "Я хожу:" << endl;
    //         int x, y;
    //         cout << "Куда тыкать (x y): ";
    //         cin >> x >> y;

    //         if (!botMap.shoot(x, y)) {
    //             player1Turn = false;
    //         }
    //     } else {
    //         cout << "Бот тыкает:" << endl;
    //         auto [x, y] = bot.makeMove(); // Бот мейк мув
    //         cout << "Бот тыкнул в (" << x << ", " << y << ")" << endl;

    //         if (!playerMap.shoot(x, y)) {
    //             player1Turn = true;
    //         }
    //     }

    //     // Завершение игры
    //     if (botMap.allShipsDestroyed()) {
    //         cout << "Я выйграл!" << endl;
    //         break;
    //     } else if (playerMap.allShipsDestroyed()) {
    //         cout << "О нет, восстание машин началось !!!" << endl;
    //         break;
    //     }
    // }

    return 0;
}