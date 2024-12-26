#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include "BattleMap.h"

class MapRenderer {
public:
    MapRenderer(const BattleMap& playerMap, const BattleMap& botMap);

    void render(std::ostream& ost) const;

private:
    const BattleMap& playerMap;
    const BattleMap& botMap;

    char getDisplayChar(BattleMap::CellStatus status, bool hideShips = false) const;
};

#endif // MAPRENDERER_H
