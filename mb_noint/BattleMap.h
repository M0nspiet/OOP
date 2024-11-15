// BattleMap.h
#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include "Ship.h"
#include "AbilityManager.h"
#include "ShipManager.h"
#include "Ability.h"  // Для способности

using namespace std;

class AbilityManager;  // Объявляем вперед

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
    bool shoot(int x, int y, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);
    void displayDouble(const BattleMap& playerMap, const BattleMap& botMap, bool hideBotShips);
    int getWidth() const;
    int getHeight() const;
    bool isShipDestroyed(int x, int y);
    void markSurroundingCells(int x, int y);
    bool allShipsDestroyed();
    CellStatus getCellStatus(int x, int y) const;
    void applyDoubleDamage(int x, int y);  // Применение способности

    vector<vector<CellStatus>> map;
    AbilityManager* abilityManager;  // Менеджер способностей

private:
    int width;
    int height;
    vector<pair<int, int>> getShipCoordinates(int x, int y);
};

#endif
