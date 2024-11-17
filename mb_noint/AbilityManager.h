#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "Ability.h"
#include "BattleMap.h"
#include "ShipManager.h"
#include <map>
#include <vector>
#include <string>

class Ability;

class AbilityManager {
public:
    // Добавляем способность в список
    void addAbility(Ability* ability);

    // Применение случайной способности (в начале игры)
    void applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

    // Вывод доступных способностей с их количеством
    void displayAbilities() const;

    // Обработка выбора способности игроком
    void handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

    // Инициализация способностей с количеством
    void initializeAbilities();

    bool isValidAbilityChoice(int choice);

    void applyAbility(int choice, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

    void assignRandomAbility();

    std::map<std::string, std::pair<Ability*, int>>& getAbilities() {
        return abilities;
    }

    // Новый метод для проверки наличия хотя бы одной способности
    bool hasAnyAbility() const;

private:
    std::map<std::string, std::pair<Ability*, int>> abilities; // Название, способность и её количество
};

#endif // ABILITYMANAGER_H