#include "GameState.h"
#include <iostream>
#include <fstream>

// Сохранение состояния игры в файл
void GameState::saveGame(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для сохранения!" << std::endl;
        return;
    }

    // Сохраняем состояния всех объектов игры
    outFile << playerMap << botMap << playerShipManager << botShipManager << *(playerMap.abilityManager) << bot;

    outFile.close();
}

// Загрузка состояния игры из файла
void GameState::loadGame(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка при открытии файла для загрузки!" << std::endl;
        throw std::runtime_error("can't load");
    }

    // Загружаем состояния всех объектов игры
    inFile >> playerMap >> botMap >> playerShipManager
           >> botShipManager >> *(playerMap.abilityManager) >> bot;
}

// Переопределение оператора вывода (сохранение)
std::ostream& operator<<(std::ostream& os, const GameState& gameState) {
    os << gameState.playerMap << gameState.botMap << gameState.playerShipManager
       << gameState.botShipManager << *(gameState.playerMap.abilityManager) << gameState.bot;
    return os;
}

// Переопределение оператора ввода (загрузка)
std::istream& operator>>(std::istream& is, GameState& gameState) {
    is >> gameState.playerMap >> gameState.botMap >> gameState.playerShipManager
       >> gameState.botShipManager >> *(gameState.playerMap.abilityManager) >> gameState.bot;
    return is;
}
