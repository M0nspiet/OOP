#ifndef GAMEUI_H
#define GAMEUI_H

#include "useraction.h"
#include <ostream>

class Game;

class GameUI {
public:
    GameUI(Game* game_);

    void print_main_menu();
    void print_inner_menu();

    void print_message(const std::string& msg); // мог бы быть вывод dialogBox

    void print_sstream(std::istream& sstr);

    friend class Game;
    Game* game;
};

#endif // GAMEUI_H  