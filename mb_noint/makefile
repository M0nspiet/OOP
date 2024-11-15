# Makefile для BattleshipGame

# Makefile для BattleshipGame

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Исходные файлы
SRCS = main.cpp BattleMap.cpp ShipManager.cpp Ship.cpp Ability.cpp Bot.cpp AbilityManager.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемый файл
TARGET = battleship_game

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
# Uncomment these lines if you're running on Windows and need UTF-8 encoding
# include <windows.h>
# SetConsoleOutputCP(CP_UTF8);
# SetConsoleCP(CP_UTF8);
