#ifndef BOT_H
#define BOT_H

#include "BattleMap.h"

using namespace std;

class ShipManager;

class Bot {
public:
    Bot() : map(nullptr), shipManager(nullptr) {} // Конструктор по умолчанию
    Bot(BattleMap& battleMap, ShipManager& shipManager);
    void placeShips();
    pair<int, int> makeMove();

    // Перегрузка операторов ввода и вывода
    friend std::ostream& operator<<(std::ostream& os, const Bot& bot);
    friend std::istream& operator>>(std::istream& is, Bot& bot);

private:
    BattleMap* map;
    ShipManager* shipManager;
    vector<pair<int, int>> previousMoves;

    pair<int, int> getRandomCoordinates();
    bool isMoveAlreadyMade(int x, int y) const;
};

#endif
