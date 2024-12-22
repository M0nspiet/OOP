#ifndef USERACTION_H
#define USERACTION_H

#include <string>
#include <map>

class Game;

namespace UserActions {

void clear_input();

struct UserAction {
    virtual ~UserAction() = default;

    virtual void read() {}
    virtual void print() {}
    UserAction(Game* game_) : game(game_){
    }

    Game* game;
};

struct NewGameAction : public UserAction {
    NewGameAction(Game* game_) : UserAction(game_){}
    void print() override;
};

struct ExitGameAction : public UserAction {
    ExitGameAction(Game* game_) : UserAction(game_){}
    void print() override;
};

struct SaveGameAction : public UserAction {
    std::string path;
    SaveGameAction(Game* game_) : UserAction(game_){}

    void print() override;
    void read() override;
};

struct LoadGameAction : public UserAction {
    std::string path;
    LoadGameAction(Game* game_) : UserAction(game_){}

    void read() override;
    void print() override;
};

struct AttackAction : public UserAction {
    int x, y;

    AttackAction(Game* game_) : UserAction(game_){}

    void read() override;
};

struct AbilityAction : public UserAction {
    bool is_active;

    AbilityAction(Game* game_) : UserAction(game_){}

    void read() override;
    void print() override;
};

char read_symbol_of(const std::string& symbols);
UserAction* menu(std::map<char, UserAction*>& actions);

}

#endif // USERACTION_H
