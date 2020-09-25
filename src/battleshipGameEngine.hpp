#pragma once
#include <vector>
#include "Coordinate.hpp"
#include "shootResultDTO.hpp"
#include "battleshipGame.hpp"

class battleshipGameEngine
{
private:
    std::vector<battleshipGame> games;
public:
    battleshipGameEngine();
    ~battleshipGameEngine();

    std::vector<bool> startGame();
    std::vector<bool> startGame(int gameboardSize);
    std::vector<bool> startGame(bool twoPlayers);
    std::vector<bool> startGame(bool twoPlayers, int gameboardSize);
    shootResultDTO shoot(int row, int col);
    shootResultDTO shoot(int playerNumber, int row, int col);
    GameStats gameStats();
};