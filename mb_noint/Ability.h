#pragma once
#include <iostream>
#include "BattleMap.h"
#include "ShipManager.h"

class Ability {
public:
    virtual ~Ability() = default;

    // Метод, применяющий способность
    virtual void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) = 0;

    // Метод для получения названия способности
    virtual std::string getName() const = 0;
};

// Класс для способности "Двойной урон"
class DoubleDamageAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Double Damage"; }
};

// Класс для способности "Сканер"
class ScannerAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Scanner"; }
};

// Класс для способности "Бомбардировка"
class BombardmentAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Bombardment"; }
};
