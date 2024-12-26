#include "Game.h"
#include <cstdlib>
#include <ctime>

#include "AbilityManager.h"
#include "GameState.h"

#include "GameRender.h"
#include "MapRender.h"

#include <sstream>

Game::Game()
    : playerMap(10, 10), 
      playerShipManager(),
      botMap(10, 10),
      botShipManager(),
      bot(botMap, botShipManager),
      who_move(WhoMove::Player),
    isGamePlayed(true), ui(this) {
    srand(static_cast<unsigned int>(time(0)));
    
    playerShipManager.placeShipsRandomly(playerMap);
    botShipManager.placeShipsRandomly(botMap);

}

void Game::runGame() {
    ui.print_main_menu();
}

void Game::game_loop(){
    while (isGamePlayed) {
        displayMap();

        if (playerMap.allShipsDestroyed()) {
            ui.print_message("О нет, бот победил! Начинаем новую игру...");

            playerMap = BattleMap(10, 10);
            playerShipManager = ShipManager();
            playerShipManager.placeShipsRandomly(playerMap);
        }

        if (botMap.allShipsDestroyed()) {
            ui.print_message("Победа пользователя, поле бота сброшено.");
            botMap = BattleMap(10, 10);
            botShipManager = ShipManager();
            botShipManager.placeShipsRandomly(botMap);

            who_move = WhoMove::Bot;
        }

        if (who_move == WhoMove::Bot) {
            botTurn();
            continue;
        }

        ui.print_inner_menu();
    }
}

void Game::call_action(UserActions::UserAction* action) {
    UserActions::ExitGameAction* exit_action = dynamic_cast<UserActions::ExitGameAction*>(action);
    UserActions::LoadGameAction* load_action = dynamic_cast<UserActions::LoadGameAction*>(action);
    UserActions::SaveGameAction* save_action = dynamic_cast<UserActions::SaveGameAction*>(action);
    UserActions::NewGameAction* newgame_action = dynamic_cast<UserActions::NewGameAction*>(action);
    UserActions::AbilityAction* ability_action = dynamic_cast<UserActions::AbilityAction*>(action);
    UserActions::AttackAction* attack_action = dynamic_cast<UserActions::AttackAction*>(action);

    if (exit_action) {
        isGamePlayed = false;
    }
    if (load_action) {
        loadGame(load_action->path);
    }
    if (save_action) {
        saveGame(save_action->path);
    }
    if (newgame_action) {
        who_move = WhoMove::Player;
        playerMap = BattleMap(10, 10);
        playerShipManager = ShipManager();
        botMap = BattleMap(10, 10);
        botShipManager = ShipManager();
        playerShipManager.placeShipsRandomly(playerMap);
        botShipManager.placeShipsRandomly(botMap);
    }
    if (ability_action) {
        if (ability_action->is_active == true) {
            playerMap.abilityManager->applyAbility(playerMap, botMap, playerShipManager, botShipManager);
        }

        delete action;
        auto secondAction = new UserActions::AttackAction(this);
        secondAction->read();

        call_action(secondAction);
    }
    if (attack_action) {
        if (false == botMap.shoot(attack_action->x, attack_action->y)) {
            who_move = WhoMove::Bot;
        }
        else {
            if (botMap.isShipDestroyed(attack_action->x, attack_action->y)) {
                ui.print_message("Корабль уничтожен!");
                if (playerMap.abilityManager) {
                    playerMap.abilityManager->assignRandomAbility();
                    ui.print_message("Получена новая способность!");
                }
            }
        }
    }

    if (action)
        delete action;
    game_loop();
}

Ability* Game::first_userAbility() {
    return playerMap.abilityManager->first_ability();
}

void Game::displayMap() {
    GameRenderer<MapRenderer> renderer(playerMap, botMap);

    stringstream messages;
    renderer.render(messages);
    ui.print_sstream(messages);
}

void Game::botTurn() {
    stringstream messages;

    auto [x, y] = bot.makeMove();

    messages << "Бот делает ход:"
             << "Бот выбрал координаты (" << x << ", " << y << ")" << std::endl;

    ui.print_sstream(messages);

    if (!playerMap.shoot(x, y)) {
        who_move = WhoMove::Player;
    }
}

void Game::saveGame(const std::string& filename) {
    GameState gameState(playerMap, botMap, playerShipManager, botShipManager, bot);

    gameState.saveGame(filename);

    stringstream messages;
    messages << "Игра сохранена в файл: " << filename << std::endl;
    ui.print_sstream(messages);
}

void Game::loadGame(const std::string& filename) {
    try {
        GameState gameState(playerMap, botMap, playerShipManager, botShipManager, bot);

        gameState.loadGame(filename);
        playerMap = gameState.playerMap;
        playerShipManager = gameState.playerShipManager;
        botMap = gameState.botMap;
        botShipManager = gameState.botShipManager;

        stringstream messages;
        messages << "Игра загружена из файла: " << filename << std::endl;
        ui.print_sstream(messages);
    }
    catch(...) {
        ui.print_message("Ошибка при загрузке игры.");
    }
}