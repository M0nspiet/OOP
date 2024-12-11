#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <fstream>
#include <string>
#include "BattleMap.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "Bot.h"

// Класс состояния игры
class GameState {
public:
    GameState(const BattleMap& playerMap, const BattleMap& botMap, const ShipManager& playerShipManager, const ShipManager& botShipManager, const AbilityManager& abilityManager, Bot& bot)
        : playerMap(playerMap), botMap(botMap), playerShipManager(playerShipManager), botShipManager(botShipManager), abilityManager(abilityManager), bot(bot) {}
    // Методы для сохранения и загрузки состояния игры
    void saveGame(const std::string& filename) const;
    void loadGame(const std::string& filename);

    // Переопределенные операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& os, const GameState& gameState);
    friend std::istream& operator>>(std::istream& is, GameState& gameState);

    // Храним состояния всех объектов игры
    BattleMap playerMap;
    BattleMap botMap;
    ShipManager playerShipManager;
    ShipManager botShipManager;
    AbilityManager abilityManager;
    Bot bot; // Добавляем бота в состояние игры
};

#endif // GAMESTATE_H