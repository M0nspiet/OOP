#include "Ship.h"

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
