#include "Ship.h"
#include <cstdlib> // Для функции rand()

Ship::Ship(int length, bool isVertical) : length(length), isVertical(isVertical) {
    segments.resize(length, State::Intact);
}

void Ship::receiveDamage(int segmentIndex) {
    if (segmentIndex < 0 || segmentIndex >= length) {
        cout << "Invalid segment index!" << endl;
        return;
    }

    if (segments[segmentIndex] == State::Intact) {
        segments[segmentIndex] = State::Damaged;
        cout << "Segment " << segmentIndex << " is now damaged." << endl;
    } else if (segments[segmentIndex] == State::Damaged) {
        segments[segmentIndex] = State::Destroyed;
        cout << "Segment " << segmentIndex << " is now destroyed." << endl;
    } else {
        cout << "Segment " << segmentIndex << " is already destroyed." << endl;
    }
}

bool Ship::hitRandomSegment() {
    // Собираем все не повреждённые сегменты
    vector<int> intactSegments;
    for (int i = 0; i < length; ++i) {
        if (segments[i] == State::Intact) {
            intactSegments.push_back(i);
        }
    }

    // Если нет неповреждённых сегментов, возвращаем false
    if (intactSegments.empty()) {
        return false;
    }

    // Выбираем случайный сегмент и наносим урон
    int randomIndex = rand() % intactSegments.size();
    receiveDamage(intactSegments[randomIndex]);
    return true;
}

bool Ship::isDestroyed() const {
    for (const auto& segment : segments) {
        if (segment != State::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::printStatus() const {
    for (int i = 0; i < length; ++i) {
        cout << "Segment " << i << ": " << stateToString(segments[i]) << endl;
    }
}

int Ship::getLength() const { return length; }
bool Ship::isVerticalOrientation() const { return isVertical; }

string Ship::stateToString(State state) const {
    switch (state) {
        case State::Intact: return "Intact";
        case State::Damaged: return "Damaged";
        case State::Destroyed: return "Destroyed";
        default: return "Unknown";
    }
}

// Перегрузка оператора вывода для Ship
ostream& operator<<(ostream& os, const Ship& ship) {
    os << ship.length << " " << ship.isVertical << " " << ship.startX << " " << ship.startY << " ";
    for (const auto& segment : ship.segments) {
        os << static_cast<int>(segment) << " ";
    }
    return os;
}

// Перегрузка оператора ввода для Ship
istream& operator>>(istream& is, Ship& ship) {
    is >> ship.length >> ship.isVertical >> ship.startX >> ship.startY;
    ship.segments.resize(ship.length);
    for (int i = 0; i < ship.length; ++i) {
        int segmentState;
        is >> segmentState;
        ship.segments[i] = static_cast<Ship::State>(segmentState);
    }
    return is;
}