#include "Check.h"
#include <iostream>

using namespace std;

// Проверка наличия способностей
void Check::checkAbility(bool hasAbility) {
    if (!hasAbility) {
        throw NoAbilitiesLeftException();
    }
}

// Проверка размещения корабля
void Check::checkShipPlacement(bool isValid) {
    if (!isValid) {
        throw ShipPlacementException();
    }
}

// Проверка атаки на границы поля
bool Check::checkAttackBounds(int x, int y, int width, int height) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return true;
}
