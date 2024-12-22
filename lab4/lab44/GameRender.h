#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "BattleMap.h"
#include <ostream>

template <typename RenderStrategy>
class GameRenderer {
public:
    GameRenderer(const BattleMap& playerMap, const BattleMap& botMap)
        : playerMap(playerMap), botMap(botMap), renderStrategy(playerMap, botMap) {}

    void render(std::ostream& ost) const {
        renderStrategy.render(ost);
    }

private:
    const BattleMap& playerMap;
    const BattleMap& botMap;
    RenderStrategy renderStrategy;
};

#endif // GAMERENDERER_H
