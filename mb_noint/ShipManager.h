#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.h"
#include "BattleMap.h"

#pragma once

class BattleMap; 

class ShipManager {
public:
    ShipManager();
    const vector<Ship>& getShips() const;
    void placeShipsRandomly(BattleMap& battleMap);

    Ship& getShip(size_t index) { return ships.at(index); }
    const Ship& getShip(size_t index) const { return ships.at(index); }
    size_t getShipCount() const { return ships.size(); }

private:
    vector<Ship> ships;
};

#endif // SHIPMANAGER_H
