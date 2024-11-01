#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.h"
#include "BattleMap.h"

class ShipManager {
public:
    ShipManager();
    void createShips();
    const vector<Ship>& getShips() const;
    void placeShipsRandomly(BattleMap& battleMap);

private:
    vector<Ship> ships;
};

#endif // SHIPMANAGER_H
