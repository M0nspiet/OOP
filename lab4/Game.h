#ifndef GAME_H
#define GAME_H

#include "BattleMap.h"
#include "ShipManager.h"
#include "Bot.h"
#include "useraction.h"
#include "GameRender.h"
#include "MapRender.h"

#include "gameui.h"

class Ability;

class Game {
public:
    Game();
    void runGame();
    
    void saveGame(const std::string& filename); // Метод сохранения игры
    void loadGame(const std::string& filename); // Метод загрузки игры
    Ability *first_userAbility();
private:
    void botTurn();
    void displayMap();
    void handleAbility();

    void call_action(UserActions::UserAction*);

    void game_loop();

    BattleMap playerMap;
    ShipManager playerShipManager;

    BattleMap botMap;
    ShipManager botShipManager;

    Bot bot;

    enum class WhoMove { Player, Bot };
    WhoMove who_move;

    bool isGamePlayed;

    friend class GameUI;

    GameUI ui;
};

#endif
