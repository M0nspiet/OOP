#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include "BattleMap.h"
#include "ShipManager.h"
#include <iostream>

class Ability {
public:
    virtual ~Ability() = default;

    // Чисто виртуальная функция для применения способности
    virtual void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) = 0;

    // Метод для получения имени способности
    virtual std::string getName() const = 0;

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Ability& ability);
    friend std::istream& operator>>(std::istream& is, Ability& ability);
};

// Примеры реализаций способностей
class DoubleDamageAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Double Damage"; }

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const DoubleDamageAbility& ability);
    friend std::istream& operator>>(std::istream& is, DoubleDamageAbility& ability);
};

class ScannerAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Scanner"; }

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const ScannerAbility& ability);
    friend std::istream& operator>>(std::istream& is, ScannerAbility& ability);
};

class BombardmentAbility : public Ability {
public:
    void apply(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) override;
    std::string getName() const override { return "Bombardment"; }

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const BombardmentAbility& ability);
    friend std::istream& operator>>(std::istream& is, BombardmentAbility& ability);
};

#endif // ABILITY_H