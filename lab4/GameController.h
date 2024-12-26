//Теперь это у нас шаблонный класс управления игрой,
//а useraction является прослойкой между классом игры (Game) 
//и шаблонным классом управления игрой (GameController)
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Game.h"
#include "useraction.h"

template <typename InputController>
class GameController {
public:
    GameController(Game* game, InputController* inputController)
        : game(game), inputController(inputController) {}

    void processInput() {
        auto action = inputController->UserAction();
        game->call_action(action);
    }

private:
    Game* game;
    InputController* inputController;
};

#endif