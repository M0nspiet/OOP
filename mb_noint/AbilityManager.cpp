#include "AbilityManager.h"
#include "Ability.h"
#include <cstdlib>  // Для rand()

// Применяем случайную способность
void AbilityManager::applyRandomAbility(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "У вас нет способностей!" << std::endl;
        return;
    }

    // Выбираем случайную способность из списка
    int randomIndex = rand() % abilities.size();
    Ability* ability = abilities[randomIndex];

    std::cout << "Применена способность: " << ability->getName() << std::endl;
    ability->apply(playerMap, botMap, playerShipManager, botShipManager);  // Применяем способность
}

// Отображение всех доступных способностей
void AbilityManager::displayAbilities() const {
    if (abilities.empty()) {
        std::cout << "Нет доступных способностей!" << std::endl;
    } else {
        std::cout << "Доступные способности: " << std::endl;
        for (const auto& ability : abilities) {
            std::cout << ability->getName() << std::endl;
        }
    }
}

void AbilityManager::handleAbilityInput(BattleMap& playerMap, BattleMap& botMap, ShipManager& playerShipManager, ShipManager& botShipManager) {
    if (abilities.empty()) {
        std::cout << "У вас нет способностей!" << std::endl;
        return;
    }

    // Отображаем все доступные способности
    std::cout << "Выберите способность для применения:" << std::endl;
    for (size_t i = 0; i < abilities.size(); ++i) {
        std::cout << (i + 1) << ". " << abilities[i]->getName() << std::endl;
    }

    // Ввод выбора пользователя
    int choice;
    std::cout << "Введите номер способности: ";
    std::cin >> choice;

    // Проверка корректности введенного номера
    if (choice < 1 || choice > static_cast<int>(abilities.size())) {
        std::cout << "Неверный выбор! Способность не применена." << std::endl;
        return;
    }

    // Применяем выбранную способность
    Ability* chosenAbility = abilities[choice - 1];
    std::cout << "Применена способность: " << chosenAbility->getName() << std::endl;
    chosenAbility->apply(playerMap, botMap, playerShipManager, botShipManager);

    // Удаляем использованную способность из списка
    abilities.erase(abilities.begin() + (choice - 1));
}
