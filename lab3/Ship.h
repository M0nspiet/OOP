#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Ship {
public:
    enum class State { // enum class для безопасности, чтобы избежать ошибок преобразования типов
        Intact,
        Damaged,
        Destroyed
    };

    Ship() : length(0), isVertical(false) {
        segments.resize(length, State::Intact);
    }

    Ship(int length, bool isVertical);

    // Получить координаты
    int getX() const { return startX; }
    int getY() const { return startY; }

    void setPosition(int x, int y) { startX = x; startY = y; }

    // Атака и статус
    void receiveDamage(int segmentIndex);
    bool hitRandomSegment(); // Новый метод
    bool isDestroyed() const;

    // Геттеры
    void printStatus() const;
    int getLength() const;
    bool isVerticalOrientation() const;

    // Перегрузка операторов ввода/вывода
    friend ostream& operator<<(ostream& os, const Ship& ship);
    friend istream& operator>>(istream& is, Ship& ship);

private:
    int startX;
    int startY;
    int length;
    bool isVertical;
    vector<State> segments;

    string stateToString(State state) const;
};

#endif // SHIP_H