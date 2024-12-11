#ifndef GAME_H
#define GAME_H

#include "BattleMap.h"
#include "ShipManager.h"
#include "Bot.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "Check.h"
#include "GameState.h"

class Game {
public:
    Game();
    void runGame();
    
    void saveGame(const std::string& filename); // Метод сохранения игры
    void loadGame(const std::string& filename); // Метод загрузки игры

private:
    void playerTurn();
    void botTurn();
    void displayMap() const;
    void handleAbility();
    void playerAttack();
    void showMenu();
    void handleMenuChoice(char choice);
    void showPostAbilityMenu();
    void handlePostAbilityChoice(char choice);

    BattleMap playerMap;
    ShipManager playerShipManager;
    BattleMap botMap;
    ShipManager botShipManager;
    Bot bot;
    AbilityManager abilityManager;
    bool player1Turn;

    GameState gameState;
};

#endif