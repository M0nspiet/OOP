#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

// Включаем необходимые заголовочные файлы в правильном порядке
#include "Ability.h"       // Для класса Ability
#include "BattleMap.h"     // Для класса BattleMap
#include "ShipManager.h"   // Для класса ShipManager

class Ability;

class AbilityManager {
public:
    // Добавляем способность в список
    void addAbility(Ability* ability) {
        abilities.push_back(ability);
    }

    // Получаем количество способностей
    int getAbilityCount() const {
        return abilities.size();
    }

    // Применяем случайную способность
    void applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

    // Отображение всех доступных способностей
    void displayAbilities() const;

    // Обработка ввода пользователя для применения способности
    void handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);

private:
    std::vector<Ability*> abilities; // Список всех способностей
};

#endif // ABILITYMANAGER_H
