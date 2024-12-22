#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <vector>
#include <iostream>
#include "Ship.h"
#include "ShipManager.h"

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

    enum class ShootType {
        Default, Double
    };

    BattleMap(int width, int height);
    bool placeShip(const Ship& ship, int x, int y);
    bool shoot(int x, int y, ShootType shootType = ShootType::Default);

    void displayDouble(const BattleMap& playerMap, const BattleMap& botMap, bool hideBotShips) ;
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

    // Объявления операторов ввода/вывода
    friend ostream& operator<<(ostream& os, const BattleMap& battleMap);
    friend istream& operator>>(istream& is, BattleMap& battleMap);
};

#endif
