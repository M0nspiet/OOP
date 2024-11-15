#include "AbilityManager.h"
#include <cstdlib>

// Метод для добавления способности
void AbilityManager::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

void AbilityManager::applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей для использования." << std::endl;
        return;
    }
    
    // Случайный выбор способности
    int randomIndex = rand() % abilities.size();
    abilities[randomIndex]->apply(playerMap, botMap, playerShipManager, botShipManager);
    std::cout << "Использована случайная способность: " << abilities[randomIndex]->getName() << std::endl;
}

// Метод для отображения доступных способностей
void AbilityManager::displayAbilities() {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей." << std::endl;
        return;
    }
    std::cout << "Доступные способности:" << std::endl;
    for (size_t i = 0; i < abilities.size(); ++i) {
        std::cout << i + 1 << ". " << abilities[i]->getName() << std::endl;
    }
}

// Метод для получения количества доступных способностей
int AbilityManager::getAbilityCount() const {
    return abilities.size();
}

// Метод для применения выбранной способности
void AbilityManager::applyAbility(int index, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (index > 0 && static_cast<size_t>(index) <= abilities.size()) {
        abilities[index - 1]->apply(playerMap, botMap, playerShipManager, botShipManager);
        std::cout << "Использована способность: " << abilities[index - 1]->getName() << std::endl;
    } else {
        std::cout << "Некорректный выбор способности." << std::endl;
    }
}