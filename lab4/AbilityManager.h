#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include "BattleMap.h"
#include "ShipManager.h"

class Ability;

class AbilityManager {
public:
    AbilityManager();

    void addAbility(Ability* ability);
    void initializeAbilities();
    void applyAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);
    void assignRandomAbility();
    void displayAbilities() const;
    void handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager);
    bool hasAnyAbility() const;
    bool isValidAbilityChoice(int choice);

    Ability* first_ability();

    // Перегрузки операторов для сериализации
    friend std::ostream& operator<<(std::ostream& os, const AbilityManager& abilityManager);
    friend std::istream& operator>>(std::istream& is, AbilityManager& abilityManager);

private:
    std::queue<Ability*> abilities;
};

#endif // ABILITYMANAGER_H
