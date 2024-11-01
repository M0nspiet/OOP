# Makefile для BattleshipGame

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -g

# Именование объектов
OBJ = main.o Ship.o ShipManager.o BattleMap.o Bot.o

# Исполняемый файл
TARGET = battleship

# Правило по умолчанию
all: $(TARGET)

# Линковка объектов
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правила компиляции
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Удаление сгенерированных файлов
clean:
	rm -f $(OBJ) $(TARGET)


#include <windows.h>
#SetConsoleOutputCP(CP_UTF8);
#SetConsoleCP(CP_UTF8);
#./BattleShip