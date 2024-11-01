// BattleMap.h
#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include "Ship.h"

using namespace std;

class BattleMap {
public:
    enum class CellStatus {
        Unknown,
        Empty,
        Ship,
        Hit,
        Miss,
        Destroyed
    };

    BattleMap(int width, int height);
    bool placeShip(const Ship& ship, int x, int y);
    bool shoot(int x, int y);
    void displayDouble(const BattleMap& playerMap, const BattleMap& botMap, bool hideBotShips);
    int getWidth() const;
    int getHeight() const;
    bool isShipDestroyed(int x, int y);
    void markSurroundingCells(int x, int y);
    bool allShipsDestroyed();

private:
    int width;
    int height;
    vector<vector<CellStatus>> map;
    vector<pair<int, int>> getShipCoordinates(int x, int y);
    //void markSurroundingCells(int x, int y);
};

#endif
