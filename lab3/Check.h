#ifndef CHECK_H
#define CHECK_H

#include <stdexcept>
#include <string>

using namespace std;

// Базовый класс для всех исключений
class GameException : public runtime_error {
public:
    explicit GameException(const string& message) : runtime_error(message) {}
};

// Исключение: Способностей больше нет
class NoAbilitiesLeftException : public GameException {
public:
    NoAbilitiesLeftException() : GameException("Ошибка: Способностей больше нет.") {}
};

// Исключение: Корабль пересекается с другим кораблем
class ShipPlacementException : public GameException {
public:
    ShipPlacementException() : GameException("Ошибка: Корабль пересекается с другим кораблем или расположен слишком близко.") {}
};

// Исключение: Атака за границами поля
class OutOfBoundsAttackException : public GameException {
public:
    OutOfBoundsAttackException() : GameException("Ошибка: Атака за границами поля.") {}
};

// Класс для проверки различных игровых ситуаций
class Check {
public:
    static void checkAbility(bool hasAbility);
    static void checkShipPlacement(bool isValid);
    static void checkAttackBounds(int x, int y, int width, int height);
};

#endif // CHECK_H
