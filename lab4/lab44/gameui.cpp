#include "gameui.h"
#include "Game.h"

GameUI::GameUI(Game* game_) : game(game_) {}

void GameUI::print_main_menu() {
    std::map<char, UserActions::UserAction*> actions = {
        {'e', new UserActions::ExitGameAction(game)},
        {'n', new UserActions::NewGameAction(game)},
        {'l', new UserActions::LoadGameAction(game)},
        {'s', new UserActions::SaveGameAction(game)}
    };

    UserActions::UserAction* selected = menu(actions);
    game->call_action(selected);
    game->game_loop();
}

void GameUI::print_inner_menu() {
    std::map<char, UserActions::UserAction*> actions = {
        {'e', new UserActions::ExitGameAction(game)},
        {'p', new UserActions::AbilityAction(game)},
        {'l', new UserActions::LoadGameAction(game)},
        {'s', new UserActions::SaveGameAction(game)}
    };

    UserActions::UserAction* selected = menu(actions);
    game->call_action(selected);
}

void GameUI::print_message(const std::string& msg) {
    std::cout << msg << "\n";
}

void GameUI::print_sstream(std::istream& sstr) {
    string str;
    while (sstr) {
        getline(sstr, str);
        cout << str << "\n";
    }
}
