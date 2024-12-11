#include "Game.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <fstream>

Game::Game()
    : playerMap(10, 10), 
      playerShipManager(), 
      botMap(10, 10), 
      botShipManager(),    
      bot(botMap, botShipManager),
      abilityManager(),
      player1Turn(true),
      gameState(playerMap, botMap, playerShipManager, botShipManager, abilityManager, bot)  // Инициализация gameState
{
    srand(static_cast<unsigned int>(time(0)));
    
    abilityManager.addAbility(new BombardmentAbility());
    abilityManager.addAbility(new DoubleDamageAbility());
    abilityManager.addAbility(new ScannerAbility());
    abilityManager.assignRandomAbility();

    playerShipManager.placeShipsRandomly(playerMap);
    botShipManager.placeShipsRandomly(botMap);
}

void Game::runGame() {
    showMenu(); // Показываем меню перед началом игры

    while (true) {
        if (playerMap.allShipsDestroyed()) {
            std::cout << "О нет, бот победил! Начинаем новую игру..." << std::endl;
            // Полный сброс игры
            playerMap = BattleMap(10, 10);
            playerShipManager = ShipManager();
            playerShipManager.placeShipsRandomly(playerMap);
            abilityManager.assignRandomAbility();
        }

        // Сброс только поля бота и его кораблей при победе игрока
        botMap = BattleMap(10, 10);
        botShipManager = ShipManager();
        botShipManager.placeShipsRandomly(botMap);

        player1Turn = true;

        while (true) {
            displayMap();

            if (player1Turn) {
                playerTurn();
            } else {
                botTurn();
            }

            if (botMap.allShipsDestroyed()) {
                std::cout << "Вы выиграли раунд! Начинается следующий раунд..." << std::endl;
                break;
            } else if (playerMap.allShipsDestroyed()) {
                break;
            }
        }
    }
}

void Game::displayMap() const {
    BattleMap& nonConstPlayerMap = const_cast<BattleMap&>(playerMap);
    nonConstPlayerMap.displayDouble(playerMap, botMap, true);
}

void Game::handleAbility() {
    if (!abilityManager.hasAnyAbility()) {
        std::cout << "У вас нет доступных способностей. Переходим к обычной стрельбе." << std::endl;
        player1Turn = false; 
        return; 
    }

    char useAbility;
    while (true) {
        std::cout << "Хотите использовать способность? (Y/N): ";
        std::cin >> useAbility;

        if (std::cin.fail() || (toupper(useAbility) != 'Y' && toupper(useAbility) != 'N')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    if (toupper(useAbility) == 'Y') {
        if (!abilityManager.hasAnyAbility()) {
            std::cout << "Нет доступных способностей!" << std::endl;
            return;
        }

        while (true) {
            std::cout << "Доступные способности:" << std::endl;
            abilityManager.displayAbilities();
            std::cout << "Введите номер способности (0 для отмены): ";
            int abilityChoice;
            std::cin >> abilityChoice;

            if (abilityChoice == 0) {
                std::cout << "Выход из меню выбора способностей." << std::endl;
                break;
            }

            if (abilityManager.isValidAbilityChoice(abilityChoice)) {
                abilityManager.applyAbility(abilityChoice, playerMap, botMap, playerShipManager, botShipManager);
                player1Turn = false;
                break;
            } else {
                std::cout << "Некорректный выбор способности! Попробуйте снова." << std::endl;
            }
        }
    } else {
        std::cout << "Переходим к обычной атаке." << std::endl;
        player1Turn = false; 
    }

    showPostAbilityMenu();
}

void Game::playerTurn() {
    std::cout << "Ваш ход:" << std::endl;
    handleAbility();  

    if (!player1Turn) {
        playerAttack();
    }
}

void Game::playerAttack() {
    int x, y;
    while (true) {
        std::cout << "Введите координаты для атаки (x y): ";
        if (!(std::cin >> x >> y)) {
            std::cout << "Ошибка ввода! Пожалуйста, введите два целых числа." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            Check::checkAttackBounds(x, y, botMap.getWidth(), botMap.getHeight());
        } catch (const OutOfBoundsAttackException& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        break;
    }

    if (!botMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
        player1Turn = false;
    }
}

void Game::botTurn() {
    std::cout << "Бот делает ход:" << std::endl;
    auto [x, y] = bot.makeMove();
    std::cout << "Бот выбрал координаты (" << x << ", " << y << ")" << std::endl;

    if (!playerMap.shoot(x, y, playerMap, botMap, playerShipManager, botShipManager)) {
        player1Turn = true;
    }
}

// Сохранение состояния игры
void Game::saveGame(const std::string& filename) {
    gameState.playerMap = playerMap;
    gameState.playerShipManager = playerShipManager;
    gameState.botMap = botMap;
    gameState.botShipManager = botShipManager;
    gameState.abilityManager = abilityManager;
    gameState.saveGame(filename);
    std::cout << "Игра сохранена в файл: " << filename << std::endl;
}

// Загрузка состояния игры
void Game::loadGame(const std::string& filename) {
    gameState.loadGame(filename);
    playerMap = gameState.playerMap;
    playerShipManager = gameState.playerShipManager;
    botMap = gameState.botMap;
    botShipManager = gameState.botShipManager;
    abilityManager = gameState.abilityManager;
    std::cout << "Игра загружена из файла: " << filename << std::endl;
}

void Game::showMenu() {
    char choice;
    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "n - начать новую игру" << std::endl;
        std::cout << "s - сохранить игру" << std::endl;
        std::cout << "l - загрузить игру" << std::endl;
        std::cin >> choice;

        if (std::cin.fail() || (choice != 'n' && choice != 's' && choice != 'l')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    handleMenuChoice(choice);
}

// Обрабатываем выбор пользователя
void Game::handleMenuChoice(char choice) {
    if (choice == 'n') {
        playerMap = BattleMap(10, 10);
        playerShipManager = ShipManager();
        botMap = BattleMap(10, 10);
        botShipManager = ShipManager();
        playerShipManager.placeShipsRandomly(playerMap);
        botShipManager.placeShipsRandomly(botMap);

        abilityManager.addAbility(new BombardmentAbility());
        abilityManager.addAbility(new DoubleDamageAbility());
        abilityManager.addAbility(new ScannerAbility());
        abilityManager.assignRandomAbility();
    } else if (choice == 's') {
        std::string filename;
        std::cout << "Введите имя файла для сохранения: ";
        std::cin >> filename;
        saveGame(filename);
    } else if (choice == 'l') {
        std::string filename;
        std::cout << "Введите имя файла для загрузки: ";
        std::cin >> filename;
        loadGame(filename);

        abilityManager.addAbility(new BombardmentAbility());
        abilityManager.addAbility(new DoubleDamageAbility());
        abilityManager.addAbility(new ScannerAbility());
        abilityManager.assignRandomAbility();
    }
}

// Показываем меню после применения или отказа от применения способностей
void Game::showPostAbilityMenu() {
    char choice;
    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "p - продолжить игру" << std::endl;
        std::cout << "s - сохранить игру" << std::endl;
        std::cout << "l - загрузить игру" << std::endl;
        std::cin >> choice;

        if (std::cin.fail() || (choice != 'p' && choice != 's' && choice != 'l')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    handlePostAbilityChoice(choice);
}

// Обрабатываем выбор пользователя после применения или отказа от применения способностей
void Game::handlePostAbilityChoice(char choice) {
    if (choice == 'p') {
        return;
    } else if (choice == 's') {
        std::string filename;
        std::cout << "Введите имя файла для сохранения: ";
        std::cin >> filename;
        saveGame(filename);
    } else if (choice == 'l') {
        std::string filename;
        std::cout << "Введите имя файла для загрузки: ";
        std::cin >> filename;
        loadGame(filename);

        // Добавляем способности только после загрузки игры
        abilityManager.addAbility(new BombardmentAbility());
        abilityManager.addAbility(new DoubleDamageAbility());
        abilityManager.addAbility(new ScannerAbility());
        abilityManager.assignRandomAbility();
    }
}