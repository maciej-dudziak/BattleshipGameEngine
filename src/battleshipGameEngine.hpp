#pragma once
#include <vector>
#include "Coordinate.hpp"
#include "shootResultDTO.hpp"
#include "battleshipGame.hpp"

enum class GameType
{
    Single,
    Duo
};

class battleshipGameEngine
{
private:
    GameType gameType;
    int turn;
    std::vector<battleshipGame> games;
public:
    battleshipGameEngine();
    ~battleshipGameEngine();

    std::vector<bool> startGame();
    std::vector<bool> startGame(int gameboardSize);
    std::vector<bool> startGame(bool twoPlayers);
    std::vector<bool> startGame(bool twoPlayers, int gameboardSize);
    shootResultDTO shoot(int row, int column);
    shootResultDTO shoot(int row, int column, int playerNumber);
    GameStats gameStats();
    GameStats gameStats(int playerNumber);
    int getCurrentTurn() { return turn; }
    GameType getGameType() { return gameType; }
private:
    shootResultDTO prepareResultObject(bool isHit, int playerNumber);
    void resetGames();
    int changeTurn(int previousTurn);
};