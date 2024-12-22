#include "Bot.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Bot::Bot(BattleMap& battleMap, ShipManager& shipManager)
    : map(&battleMap), shipManager(&shipManager) {
    srand(static_cast<unsigned int>(time(0)));
}

void Bot::placeShips() {
    shipManager->placeShipsRandomly(*map);
}

pair<int, int> Bot::makeMove() {
    int x, y;
    do {
        tie(x, y) = getRandomCoordinates();
    } while (isMoveAlreadyMade(x, y));
    
    previousMoves.push_back({x, y});
    return {x, y};
}

pair<int, int> Bot::getRandomCoordinates() {
    int x = rand() % map->getWidth();
    int y = rand() % map->getHeight();
    return {x, y};
}

bool Bot::isMoveAlreadyMade(int x, int y) const {
    for (const auto& move : previousMoves) {
        if (move.first == x && move.second == y) {
            return true;
        }
    }
    return false;
}

// Перегрузка оператора вывода (сохранение)
std::ostream& operator<<(std::ostream& os, const Bot& bot) {
    os << bot.previousMoves.size() << " ";
    for (const auto& move : bot.previousMoves) {
        os << move.first << " " << move.second << " ";
    }
    return os;
}

// Перегрузка оператора ввода (загрузка)
std::istream& operator>>(std::istream& is, Bot& bot) {
    size_t moveCount;
    is >> moveCount;
    bot.previousMoves.resize(moveCount);
    for (size_t i = 0; i < moveCount; ++i) {
        is >> bot.previousMoves[i].first >> bot.previousMoves[i].second;
    }
    return is;
}