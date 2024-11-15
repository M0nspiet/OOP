#pragma once
#include <vector>
#include <iostream>
#include "Ability.h"

class AbilityManager {
private:
    std::vector<Ability*> abilities;

public:
    // Добавить новую способность
    void addAbility(Ability* ability);

    // Отобразить все доступные способности
    void displayAbilities();

    void applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

    // Получить количество доступных способностей
    int getAbilityCount() const;

    // Применить выбранную способность по индексу
    void applyAbility(int index, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);
};
