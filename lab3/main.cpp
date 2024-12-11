#include <iostream>
#include <windows.h>
#include "Game.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Game game;

    std::cout << "Добро пожаловать в игру!" << std::endl;
    
    game.runGame();
    
    std::cout << "Спасибо за игру!" << std::endl;
    return 0;
}