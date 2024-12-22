#include "MapRender.h"
#include <ostream>

using namespace std;

MapRenderer::MapRenderer(const BattleMap& playerMap, const BattleMap& botMap)
    : playerMap(playerMap), botMap(botMap) {}

void MapRenderer::render(ostream &ost) const {
    ost << "Поле игрока" << string(22, ' ') << "Поле бота" << endl;

    ost << "  ";
    for (int col = 0; col < playerMap.getWidth(); ++col) {
        ost << col << " ";
    }
    ost << string(8, ' ');
    ost << "  ";
    for (int col = 0; col < botMap.getWidth(); ++col) {
        ost << col << " ";
    }
    ost << endl;

    for (int row = 0; row < playerMap.getHeight(); ++row) {
        ost << row << " ";
        for (BattleMap::CellStatus cell : playerMap.map[row]) {
            ost << getDisplayChar(cell) << " ";
        }

        ost << string(8, ' ');

        ost << row << " ";
        for (BattleMap::CellStatus cell : botMap.map[row]) {
            ost << getDisplayChar(cell, true) << " ";
        }

        ost << endl;
    }
}

char MapRenderer::getDisplayChar(BattleMap::CellStatus status, bool hideShips) const {
    switch (status) {
        case BattleMap::CellStatus::Unknown: return '.';
        case BattleMap::CellStatus::Empty: return ' ';
        case BattleMap::CellStatus::Ship: return hideShips ? '.' : 'S';
        case BattleMap::CellStatus::Hit: return 'X';
        case BattleMap::CellStatus::Miss: return 'O';
        case BattleMap::CellStatus::Destroyed: return '#';
        default: return '?';
    }
}

// красивая отрисовка
// MapRenderer::MapRenderer(const BattleMap& playerMap, const BattleMap& botMap)
//     : playerMap(playerMap), botMap(botMap) {}

// void MapRenderer::render() const {
//     // Заголовок
//     ost << "Поле игрока" << string(15, ' ') << "Поле бота" << endl;

//     // Верхняя строка с координатами столбцов
//     ost << "  ";
//     for (int col = 0; col < playerMap.getWidth(); ++col) {
//         ost << "| " << col << " ";
//     }
//     ost << "|" << string(8, ' ');
//     ost << "  ";
//     for (int col = 0; col < botMap.getWidth(); ++col) {
//         ost << "| " << col << " ";
//     }
//     ost << "|" << endl;

//     // Верхняя граница
//     ost << "  ";
//     for (int col = 0; col < playerMap.getWidth(); ++col) {
//         ost << "+---";
//     }
//     ost << "+" << string(8, ' ');
//     ost << "  ";
//     for (int col = 0; col < botMap.getWidth(); ++col) {
//         ost << "+---";
//     }
//     ost << "+" << endl;

//     // Основная часть карты
//     for (int row = 0; row < playerMap.getHeight(); ++row) {
//         // Левая граница
//         ost << row << " ";

//         // Содержимое карты игрока
//         for (BattleMap::CellStatus cell : playerMap.map[row]) {
//             ost << "| " << getDisplayChar(cell) << " ";
//         }
//         ost << "|" << string(8, ' ');

//         // Содержимое карты бота
//         ost << row << " ";
//         for (BattleMap::CellStatus cell : botMap.map[row]) {
//             ost << "| " << getDisplayChar(cell, true) << " ";
//         }
//         ost << "|" << endl;

//         // Нижняя граница
//         ost << "  ";
//         for (int col = 0; col < playerMap.getWidth(); ++col) {
//             ost << "+---";
//         }
//         ost << "+" << string(8, ' ');
//         ost << "  ";
//         for (int col = 0; col < botMap.getWidth(); ++col) {
//             ost << "+---";
//         }
//         ost << "+" << endl;
//     }
// }

// char MapRenderer::getDisplayChar(BattleMap::CellStatus status, bool hideShips) const {
//     switch (status) {
//         case BattleMap::CellStatus::Unknown: return '.';
//         case BattleMap::CellStatus::Empty: return ' ';
//         case BattleMap::CellStatus::Ship: return hideShips ? '.' : 'S';
//         case BattleMap::CellStatus::Hit: return 'X';
//         case BattleMap::CellStatus::Miss: return 'O';
//         case BattleMap::CellStatus::Destroyed: return '#';
//         default: return '?';
//     }
// }
