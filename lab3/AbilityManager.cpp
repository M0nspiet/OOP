#include "AbilityManager.h"
#include "Ability.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <random>

// Очередь способностей теперь используется
void AbilityManager::addAbility(Ability* ability) {
    abilities.push(ability);  // Добавляем способность в очередь
}

void AbilityManager::initializeAbilities() {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
        return;
    }

    // Перемешиваем очередь случайным образом
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<Ability*> tempAbilities;

    while (!abilities.empty()) {
        tempAbilities.push_back(abilities.front());
        abilities.pop();
    }

    std::shuffle(tempAbilities.begin(), tempAbilities.end(), g);

    // Перезаполняем очередь случайно перемешанными способностями
    for (auto& ability : tempAbilities) {
        abilities.push(ability);
    }
}

// Применение первой способности из очереди
void AbilityManager::applyAbility(int choice, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
        return;
    }

    // Применение первой способности из очереди
    Ability* abilityToUse = abilities.front();
    abilities.pop();  // Удаление способности из очереди после применения

    std::cout << "Применена способность: " << abilityToUse->getName() << std::endl;
    abilityToUse->apply(playerMap, botMap, playerShipManager, botShipManager);
}

// Метод для добавления случайной способности при уничтожении вражеского корабля
void AbilityManager::assignRandomAbility() {
    std::vector<Ability*> allAbilities = {new DoubleDamageAbility(), new ScannerAbility(), new BombardmentAbility()};

    // Генерируем случайный индекс и добавляем способность в очередь
    int randomIndex = rand() % allAbilities.size();
    abilities.push(allAbilities[randomIndex]);
    std::cout << "Добавлена случайная способность: " << allAbilities[randomIndex]->getName() << std::endl;
}

void AbilityManager::displayAbilities() const {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
    } else {
        std::cout << "Доступная способность: " << abilities.front()->getName() << std::endl;
    }
}

void AbilityManager::handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    while (true) {
        displayAbilities(); // Показываем только одну доступную способность
        std::cout << "Вы хотите использовать эту способность? (Y/N): ";

        char useAbility;
        std::cin >> useAbility;

        if (std::cin.fail() || (toupper(useAbility) != 'Y' && toupper(useAbility) != 'N')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова." << std::endl;
            continue;
        }

        if (toupper(useAbility) == 'Y') {
            applyAbility(1, playerMap, botMap, playerShipManager, botShipManager); // Применяем первую способность в очереди
            break; // Завершаем цикл после применения способности
        } else {
            std::cout << "Выход из меню выбора способности." << std::endl;
            break;
        }
    }
}

bool AbilityManager::hasAnyAbility() const {
    return !abilities.empty();  // Проверка на пустоту очереди
}

bool AbilityManager::isValidAbilityChoice(int choice) {
    return choice >= 1 && choice <= static_cast<int>(abilities.size());
}

std::ostream& operator<<(std::ostream& os, const AbilityManager& abilityManager) {
    // Записываем количество способностей
    os << abilityManager.abilities.size() << std::endl;

    // Проходим по очереди и записываем каждую способность
    std::queue<Ability*> tempAbilities = abilityManager.abilities;
    while (!tempAbilities.empty()) {
        Ability* ability = tempAbilities.front();
        if (auto* d = dynamic_cast<DoubleDamageAbility*>(ability)) {
            os << *d << std::endl;
        } else if (auto* s = dynamic_cast<ScannerAbility*>(ability)) {
            os << *s << std::endl;
        } else if (auto* b = dynamic_cast<BombardmentAbility*>(ability)) {
            os << *b << std::endl;
        }
        tempAbilities.pop();
    }

    return os;
}

std::istream& operator>>(std::istream& is, AbilityManager& abilityManager) {
    size_t abilityCount;
    is >> abilityCount;

    for (size_t i = 0; i < abilityCount; ++i) {
        std::string type;
        is >> type;
        if (type == "DoubleDamageAbility") {
            abilityManager.abilities.push(new DoubleDamageAbility());
        } else if (type == "ScannerAbility") {
            abilityManager.abilities.push(new ScannerAbility());
        } else if (type == "BombardmentAbility") {
            abilityManager.abilities.push(new BombardmentAbility());
        }
    }

    return is;
}