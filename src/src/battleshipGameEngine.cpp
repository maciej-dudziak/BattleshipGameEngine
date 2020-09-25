#include "../battleshipGameEngine.hpp"
#include <iostream>
battleshipGameEngine::battleshipGameEngine()
{
    games.push_back(battleshipGame());
}

battleshipGameEngine::~battleshipGameEngine()
{  
}

std::vector<bool> battleshipGameEngine::startGame()
{
    games[0].placeAllShips();
    return games[0].getGameboard();
}

std::vector<bool> battleshipGameEngine::startGame(int newGameboardSize)
{
    if(newGameboardSize < 6)
    {
        return std::vector<bool>();
    }
    games[0].resizeGame(newGameboardSize);
    return startGame();
}

std::vector<bool> battleshipGameEngine::startGame(bool twoPlayers)
{
    if(twoPlayers)
    {
        games.push_back(battleshipGame());
        games[1].placeAllShips();
    }
    return startGame();
}

std::vector<bool> battleshipGameEngine::startGame(bool twoPlayers, int gameboardSize)
{
    if(twoPlayers)
    {
        games.push_back(battleshipGame());
        games[1].resizeGame(gameboardSize);
        games[1].placeAllShips();
    }
    return startGame(gameboardSize);
}

shootResultDTO battleshipGameEngine::shoot(int playerNumber, int const row, int const column)
{
    auto targetCoordinate = 
        Coordinate::builder().withRow(row).withColumn(column).build();
    bool isHit = games.at(playerNumber-1).isShipHit(targetCoordinate);
    int shipCount = games.at(playerNumber-1).getShipCount();
    auto shipPlacement = games.at(playerNumber-1).getGameboard();
    auto hitsAndMisses = games.at(playerNumber-1).getHitsAndMisses();
    shootResultDTO result = shootResultDTO::builder().withIsHit(isHit)
                                                    .withShipPlacingVector(shipPlacement)
                                                    .withHitsAndMissesVector(hitsAndMisses)
                                                    .withShipsLeftCount(shipCount)
                                                    .build();

    return result;
}

shootResultDTO battleshipGameEngine::shoot(int row, int col)
{
    return shoot(1, row, col);
}

GameStats battleshipGameEngine::gameStats()
{
    return games.at(0).getGameStats();
}