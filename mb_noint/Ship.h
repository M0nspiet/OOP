#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Ship {
public:
    enum class State { //enum class используем для безопасности класса, что бы небыло ошибок в преобразовании типов
        Intact,
        Damaged,
        Destroyed
    };

    Ship(int length, bool isVertical);
    void receiveDamage(int segmentIndex);
    void printStatus() const;
    int getLength() const;
    bool isVerticalOrientation() const;
    int getX() const { return startX; }
    int getY() const { return startY; }

private:
    int startX;
    int startY;
    int length;
    bool isVertical;
    vector<State> segments;

    string stateToString(State state) const;
};

#endif
