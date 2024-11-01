#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <stdexcept>

using namespace std;

class Ship {
public:
    enum class State {
        Intact,
        Damaged,
        Destroyed
    };

    Ship(int length, bool isVertical) : length(length), isVertical(isVertical) {
        segments.resize(length, State::Intact);
    }

    void receiveDamage(int segmentIndex) {
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

    void printStatus() const {
        for (int i = 0; i < length; ++i) {
            cout << "Segment " << i << ": " << stateToString(segments[i]) << endl;
        }
    }

    int getLength() const { return length; }
    bool isVerticalOrientation() const { return isVertical; }

private:
    int length;
    bool isVertical;
    vector<State> segments;

    string stateToString(State state) const {
        switch (state) {
            case State::Intact: return "Intact";
            case State::Damaged: return "Damaged";
            case State::Destroyed: return "Destroyed";
            default: return "Unknown";
        }
    }
};

class BattleMap;

class ShipManager {
public:
    ShipManager() {
        vector<int> sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // 1 линкор, 2 крейсера, 3 эсминца, 4 катера
        for (int size : sizes) {
            ships.emplace_back(size, rand() % 2); // Случайная ориентация (вертикально/горизонтально)
        }
    }

    const vector<Ship>& getShips() const {
        return ships;
    }

    void placeShipsRandomly(BattleMap& battleMap);

private:
    vector<Ship> ships;
};

class BattleMap {
public:
    enum class CellStatus {
        Unknown,
        Empty,
        Ship
    };

    BattleMap(int width, int height) : width(width), height(height) {
        if (width <= 0 || height <= 0) {
            throw invalid_argument("Width and height must be positive.");
        }
        map.resize(height, vector<CellStatus>(width, CellStatus::Unknown));
    }

    bool placeShip(const Ship& ship, int x, int y) {
        if (ship.isVerticalOrientation()) {
            if (y + ship.getLength() > height) return false; // Проверка выхода за границы
            for (int i = -1; i <= ship.getLength(); ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int ny = y + i;
                    int nx = x + j;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != CellStatus::Unknown) {
                        return false; // Проверка на занятость соседних клеток
                    }
                }
            }
            for (int i = 0; i < ship.getLength(); ++i) {
                map[y + i][x] = CellStatus::Ship; // Размещение корабля
            }
        } else {
            if (x + ship.getLength() > width) return false; // Проверка выхода за границы
            for (int i = -1; i <= ship.getLength(); ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nx = x + i;
                    int ny = y + j;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != CellStatus::Unknown) {
                        return false; // Проверка на занятость соседних клеток
                    }
                }
            }
            for (int i = 0; i < ship.getLength(); ++i) {
                map[y][x + i] = CellStatus::Ship; // Размещение корабля
            }
        }
        return true;
    }

    void display() const {
        cout << "Current Battle Map:" << endl;
        for (const auto& row : map) {
            for (CellStatus cell : row) {
                string displayChar;
                switch (cell) {
                    case CellStatus::Unknown: displayChar = '.'; break;
                    case CellStatus::Empty: displayChar = ' '; break;
                    case CellStatus::Ship: displayChar = 'S'; break;
                }
                cout << displayChar << ' ';
            }
            cout << endl;
        }
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width;
    int height;
    vector<vector<CellStatus>> map;
};

// Расстановка кораблей рандомно
void ShipManager::placeShipsRandomly(BattleMap& battleMap) {
    for (const Ship& ship : ships) {
        bool placed = false;
        while (!placed) {
            int x = rand() % battleMap.getWidth();
            int y = rand() % battleMap.getHeight();
            bool isVertical = rand() % 2; // Random orientation

            Ship randomShip(ship.getLength(), isVertical);
            placed = battleMap.placeShip(randomShip, x, y);
        }
    }
}

int main() {
    srand(time(0));
    int width = 10, height = 10;

    // Create battle maps and ship managers for both players
    BattleMap battleMap1(width, height);
    ShipManager shipManager1;
    BattleMap battleMap2(width, height);
    ShipManager shipManager2;

    // Player 1 places ships
    // cout << "Player 1, place your ships on the map." << endl;
    // const vector<Ship>& ships1 = shipManager1.getShips();
    // for (int i = 0; i < ships1.size(); ++i) {
    //     int x, y;
    //     char orientation;
    //     bool placed = false;

    //     while (!placed) {
    //         cout << "Placing ship " << (i + 1) << " of length " << ships1[i].getLength() << "." << endl;
    //         cout << "Enter x, y coordinates and orientation (v/h): ";
    //         cin >> x >> y >> orientation;

    //         bool isVertical = (orientation == 'v');
    //         Ship ship(ships1[i].getLength(), isVertical);

    //         if (battleMap1.placeShip(ship, x, y)) {
    //             cout << "Ship " << (i + 1) << " placed successfully!" << endl;
    //             placed = true;
    //         } else {
    //             cout << "Failed to place ship " << (i + 1) << ". Try again." << endl;
    //         }
    //     }
    //     battleMap1.display(); 
    // }

    // Выводим поле первого игрока
    cout << "Player 1, placing your ships randomly on the map." << endl;
    shipManager1.placeShipsRandomly(battleMap1);
    battleMap1.display(); 

    //cout << "Player 2, place your ships on the map." << endl;
    // const vector<Ship>& ships2 = shipManager2.getShips();
    // for (int i = 0; i < ships2.size(); ++i) {
    //     int x, y;
    //     char orientation;
    //     bool placed = false;

    //     while (!placed) {
    //         cout << "Placing ship " << (i + 1) << " of length " << ships2[i].getLength() << "." << endl;
    //         cout << "Enter x, y coordinates and orientation (v/h): ";
    //         cin >> x >> y >> orientation;

    //         bool isVertical = (orientation == 'v');
    //         Ship ship(ships2[i].getLength(), isVertical);

    //         if (battleMap2.placeShip(ship, x, y)) {
    //             cout << "Ship " << (i + 1) << " placed successfully!" << endl;
    //             placed = true;
    //         } else {
    //             cout << "Failed to place ship " << (i + 1) << ". Try again." << endl;
    //         }
    //     }
    //     battleMap2.display(); 
    // }
    cout << "Player 2, placing your ships randomly on the map." << endl; //
    shipManager2.placeShipsRandomly(battleMap2); //Randof plased on the map
    battleMap2.display();

    return 0;
}