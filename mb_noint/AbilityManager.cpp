#include "AbilityManager.h"
#include <iostream>
#include <cstdlib> // Для rand()

// struct AbilityEntry {
//     Ability* ability;
//     int count;
// };

void AbilityManager::addAbility(Ability* ability) {
    const std::string& name = ability->getName();
    if (abilities.find(name) == abilities.end()) {
        abilities[name] = {ability, 1}; // Добавляем способность с количеством 1
    } else {
        abilities[name].second++; // Увеличиваем количество
    }
}

// Инициализация случайной способности в начале игры
void AbilityManager::initializeAbilities() {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
        return;
    }

    // Применяем случайную способность
    int randomIndex = rand() % abilities.size();
    auto it = std::next(abilities.begin(), randomIndex);
    it->second.second++; // Увеличиваем количество случайной способности
}

void AbilityManager::applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
        return;
    }

    int randomIndex = rand() % abilities.size();
    auto it = std::next(abilities.begin(), randomIndex);

    std::cout << "Применена случайная способность: " << it->first << std::endl;
    it->second.first->apply(playerMap, botMap, playerShipManager, botShipManager);

    if (--it->second.second == 0) {
        abilities.erase(it);
    }
}

void AbilityManager::displayAbilities() const {
    std::cout << "Доступные способности:" << std::endl;
    
    // Список всех возможных способностей
    std::map<std::string, Ability*> allAbilities = {
        {"DoubleDamage", new DoubleDamageAbility()},
        {"Scanner", new ScannerAbility()},
        {"Bombardment", new BombardmentAbility()}
    };
    
    // Вывод всех способностей, даже если их количество 0
    int index = 1;
    for (const auto& abilityPair : allAbilities) {
        auto it = abilities.find(abilityPair.first);
        int count = (it != abilities.end()) ? it->second.second : 0;  // Если способность есть, выводим её количество, иначе 0
        std::cout << index++ << ". " << abilityPair.first << " (" << count << " шт)" << std::endl;
    }
}


void AbilityManager::handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей для использования!" << std::endl;
        return;
    }

    displayAbilities(); // Показываем список способностей

    int choice;
    std::cout << "Введите номер способности: ";
    std::cin >> choice;

    // Проверка на правильность выбора способности
    if (choice < 1 || choice > static_cast<int>(abilities.size())) {
        std::cout << "Неверный выбор! Способность не применена." << std::endl;
        return;
    }

    // Перемещаем итератор к выбранной способности
    auto it = std::next(abilities.begin(), choice - 1);
    std::string abilityName = it->first;

    // Проверяем, доступна ли выбранная способность
    if (it->second.second > 0) {
        std::cout << "Применена способность: " << abilityName << std::endl;
        it->second.first->apply(playerMap, botMap, playerShipManager, botShipManager);

        // Уменьшаем количество использованных способностей
        if (--it->second.second == 0) {
            abilities.erase(it);  // Удаляем способность из списка, если она закончилась
        }
    } else {
        std::cout << "Способность " << abilityName << " закончилась и не может быть использована!" << std::endl;
    }
}

bool AbilityManager::isValidAbilityChoice(int choice) {
    auto it = abilities.begin();
    std::advance(it, choice - 1); // Перемещаем итератор на нужную позицию
    return it != abilities.end() && it->second.second > 0;  // Проверяем количество способностей
}

void AbilityManager::applyAbility(int choice, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    auto it = abilities.begin();
    std::advance(it, choice - 1);  // Перемещаем итератор на нужную позицию

    if (it != abilities.end() && it->second.second > 0) {  // Проверяем, есть ли способность
        it->second.first->apply(playerMap, botMap, playerShipManager, botShipManager);  // Применяем способность
        it->second.second--;  // Уменьшаем количество использованных способностей
    } else {
        cout << "Невозможное использование этой способности!" << endl;
    }
}

void AbilityManager::assignRandomAbility() {
    // Очищаем список способностей перед началом игры, чтобы не было дублирования
    abilities.clear();

    // Создаем массив с указателями на все способности
    vector<Ability*> allAbilities = {new DoubleDamageAbility(), new ScannerAbility(), new BombardmentAbility()};
    
    // Генерация случайного индекса для выбора одной способности
    int randomIndex = rand() % allAbilities.size();

    // Добавляем только одну выбранную способность
    switch(randomIndex) {
        case 0:
            abilities["DoubleDamage"] = {allAbilities[randomIndex], 1};
            break;
        case 1:
            abilities["Scanner"] = {allAbilities[randomIndex], 1};
            break;
        case 2:
            abilities["Bombardment"] = {allAbilities[randomIndex], 1};
            break;
    }
}