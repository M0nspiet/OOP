#include "AbilityManager.h"
#include <iostream>
#include <cstdlib>
#include <limits>

void AbilityManager::addAbility(Ability* ability) {
    const std::string& name = ability->getName();
    if (abilities.find(name) == abilities.end()) {
        abilities[name] = {ability, 1};
    } else {
        abilities[name].second++;
    }
}

void AbilityManager::initializeAbilities() {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
        return;
    }

    int randomIndex = rand() % abilities.size();
    auto it = std::next(abilities.begin(), randomIndex);
    it->second.second++;
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
    cout << "Доступные способности:" << endl;

    std::map<std::string, Ability*> allAbilities = {
        {"Bombardment", new BombardmentAbility()},
        {"DoubleDamage", new DoubleDamageAbility()},
        {"Scanner", new ScannerAbility()}
    };

    int index = 1;
    for (const auto& abilityPair : allAbilities) {
        auto it = abilities.find(abilityPair.first);
        int count = (it != abilities.end()) ? it->second.second : 0;
        cout << index++ << ". " << abilityPair.first << " (" << count << " шт)" << endl;
    }

    cout << "0. Выход из меню" << endl;
}

// void AbilityManager::displayAbilities() const {
//     cout << "Доступные способности:" << endl;

//     int index = 1; // Индекс для отображения пользователю
//     for (const auto& abilityPair : abilities) {
//         const std::string& abilityName = abilityPair.first;
//         int count = abilityPair.second.second; // Количество способностей

//         if (count > 0) {
//             cout << index++ << ". " << abilityName << " (" << count << " шт)" << endl;
//         }
//     }

//     // Показываем выход из меню
//     cout << "0. Выход из меню" << endl;
// }


void AbilityManager::handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    while (true) {
        displayAbilities(); // Выводим список всех способностей
        cout << "Введите номер способности (или 0 для выхода): ";

        int choice;
        cin >> choice;

        // Проверка корректности ввода
        if (cin.fail()) {
            cin.clear(); // Сброс флага ошибки
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            cout << "Некорректный ввод. Пожалуйста, введите номер способности." << endl;
            continue;
        }

        // Выход из меню при выборе 0
        if (choice == 0) {
            cout << "Выход из меню выбора способностей." << endl;
            break;
        }

        // Проверка, что выбранная способность действительна
        if (!isValidAbilityChoice(choice)) {
            cout << "Некорректный выбор способности. Попробуйте снова." << endl;
            continue;
        }

        // Применяем выбранную способность
        applyAbility(choice, playerMap, botMap, playerShipManager, botShipManager);
        break; // Завершаем цикл после успешного применения способности
    }
}

bool AbilityManager::isValidAbilityChoice(int choice) {
    if (choice < 1 || choice > 3) { // Проверка диапазона (от 1 до 3)
        return false;
    }

    // Список всех возможных способностей
    std::map<std::string, Ability*> allAbilities = {
        {"Bombardment", new BombardmentAbility()},
        {"DoubleDamage", new DoubleDamageAbility()},
        {"Scanner", new ScannerAbility()}
    };

    // Проверяем наличие и количество по индексу
    auto it = allAbilities.begin();
    std::advance(it, choice - 1); // Смещаем итератор на выбранный элемент
    const std::string& abilityName = it->first;

    auto found = abilities.find(abilityName);
    if (found == abilities.end() || found->second.second <= 0) {
        return false;
    }

    return true;
}

void AbilityManager::applyAbility(int choice, BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    // Список всех возможных способностей
    std::map<std::string, Ability*> allAbilities = {
        {"Bombardment", new BombardmentAbility()},
        {"DoubleDamage", new DoubleDamageAbility()},
        {"Scanner", new ScannerAbility()}
    };

    auto it = allAbilities.begin();
    std::advance(it, choice - 1); // Смещаем итератор на выбранный элемент
    const std::string& abilityName = it->first;

    auto found = abilities.find(abilityName);
    if (found != abilities.end() && found->second.second > 0) {
        cout << "Применена способность: " << abilityName << endl;
        found->second.first->apply(playerMap, botMap, playerShipManager, botShipManager);
        found->second.second--; // Уменьшаем количество использований способности
    } else {
        cout << "Способность " << abilityName << " недоступна!" << endl;
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

bool AbilityManager::hasAnyAbility() const {
    for (const auto& ability : abilities) {
        if (ability.second.second > 0) { // Если количество больше нуля
            return true;
        }
    }
    return false;
}