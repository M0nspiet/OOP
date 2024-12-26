#include "useraction.h"

#include <iostream>
#include <limits>
#include <algorithm>
#include <ios>
#include "Check.h"
#include "Ability.h"

#include "Game.h"

void UserActions::clear_input() {
    std::cin.clear();
    if (std::cin.peek() != std::ios::traits_type::eof())
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void print_actions(std::map<char, UserActions::UserAction*>& actions) {
    std::cout << "Выберите действие:" << std::endl;
    for (auto& action : actions) {
        std::cout << "\t" << action.first << " - ";
        action.second->print();
        std::cout << "\n";
    }
}

std::string current_actions_symbols(std::map<char, UserActions::UserAction*>& actions) {
    std::string symbols;

    for (auto& action : actions) {
        symbols += action.first;
    }

    return symbols;
}

void UserActions::NewGameAction::print() {
    std::cout << "начать новую игру" << std::endl;
}

void UserActions::ExitGameAction::print() {
    std::cout << "exit" << std::endl;
}

void UserActions::SaveGameAction::read() {
    std::cout << "filename: ";

    while (true) {
        std::getline(std::cin, path);
        if (path.empty() == false)
            break;
    }
}

void UserActions::SaveGameAction::print() {
    std::cout << "сохранить игру" << std::endl;
}

void UserActions::LoadGameAction::read() {
    std::cout << "filename: ";

    while (true) {
        std::getline(std::cin, path);
        if (path.empty() == false)
            break;
    }
}

void UserActions::LoadGameAction::print() {
    std::cout << "загрузить игру" << std::endl;
}

void UserActions::AttackAction::read() {
    while (true) {
        std::cout << "Введите координаты для атаки (x y): ";

        std::cin >> x >> y;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите числа от 0 до 9\n";
            continue;
        }

        if (false == Check::checkAttackBounds(x, y, 10, 10)) {
            std::cout << "Введите числа от 0 до 9.\n";
            continue;
        }

        break;
    }
}

void UserActions::AbilityAction::read() {
    Ability* ability = this->game->first_userAbility();
    is_active = false;

    if (nullptr == ability) {
        return;
    }

    std::cout << "Вы хотите использовать способность? Введи Y или N ";
    if (tolower(read_symbol_of("YyNn")) != 'y') {
        return;
    }

    cout << "Доступная способность: " << ability->getName() << "\n";
    std::cout << "Точно будем использовать? Введи Y или N ";
    is_active = tolower(read_symbol_of("YyNn")) == 'y';
}

void UserActions::AbilityAction::print() {
    std::cout << "продолжить игру" << std::endl;
}

char UserActions::read_symbol_of(const std::string& symbols) {
    char c;

    while (true) {
        std::cin >> c;
        if (std::cin.peek() != '\n') {
            continue;
        }

        if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
            return c;
        }
        clear_input();
    }
}

UserActions::UserAction* UserActions::menu(std::map<char, UserAction*>& actions) {
    print_actions(actions);

    char choice = read_symbol_of(current_actions_symbols(actions));
    actions[choice]->read();

    return actions[choice];
}
