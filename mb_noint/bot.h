#ifndef BOT_H
#define BOT_H

#include "BattleMap.h"
#include "ShipManager.h"
#include "Ability.h"
#include "AbilityManager.h"

using namespace std;

class Bot {
public:
    Bot(BattleMap& battleMap, ShipManager& shipManager);
    void placeShips();
    pair<int, int> makeMove();

private:
    BattleMap& map;
    ShipManager& shipManager;
    vector<pair<int, int>> previousMoves;

    pair<int, int> getRandomCoordinates();
    bool isMoveAlreadyMade(int x, int y) const;
};

#endif
