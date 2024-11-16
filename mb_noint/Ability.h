#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include "BattleMap.h"
#include "ShipManager.h"

class Ability {
public:
    virtual ~Ability() = default;

    // Чисто виртуальная функция для применения способности
    virtual void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) = 0;

    // Метод для получения имени способности
    virtual std::string getName() const = 0;
};

// Примеры реализаций способностей
class DoubleDamageAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Double Damage"; }
};

class ScannerAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Scanner"; }
};

class BombardmentAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Bombardment"; }
};

#endif // ABILITY_H
