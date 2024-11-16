# Makefile для BattleshipGame

# Makefile для BattleshipGame

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Исходные файлы
SRCS = main.cpp BattleMap.cpp ShipManager.cpp Ship.cpp Ability.cpp AbilityManager.cpp Bot.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемый файл
TARGET = BattleShip

# Правило по умолчанию
all: $(TARGET)

# Линковка объектов в исполняемый файл
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило для создания объектных файлов из исходных
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка промежуточных файлов
clean:
	rm -f $(OBJS) $(TARGET)
# Правила для использования UTF-8 в Windows (необязательно)
# include <windows.h>
# SetConsoleOutputCP(CP_UTF8);
# SetConsoleCP(CP_UTF8);

#Если не хочет запускаться вводим по другому:
#g++ -std=c++17 -Wall -g -c AbilityManager.cpp -o AbilityManager.o
#g++ -std=c++17 -Wall -g -c main.cpp -o main.o
#g++ -std=c++17 -Wall -g -o BattleShip main.o BattleMap.o ShipManager.o Ship.o Ability.o AbilityManager.o Bot.o