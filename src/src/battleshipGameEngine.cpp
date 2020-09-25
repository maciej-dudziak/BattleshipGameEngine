#include "../battleshipGameEngine.hpp"
#include <iostream>
battleshipGameEngine::battleshipGameEngine()
{
    turn = 1;
    gameType = GameType::Single;
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
        gameType = GameType::Duo;
        games.push_back(battleshipGame());
        games[1].placeAllShips();
    }
    return startGame();
}

std::vector<bool> battleshipGameEngine::startGame(bool twoPlayers, int gameboardSize)
{
    if(twoPlayers)
    {
        gameType = GameType::Duo;
        games.push_back(battleshipGame());
        games[1].resizeGame(gameboardSize);
        games[1].placeAllShips();
    }
    return startGame(gameboardSize);
}

shootResultDTO battleshipGameEngine::shoot(int row, int column, int playerNumber)
{
    bool isHit = false;
    if(turn == playerNumber)
    {
        auto targetCoordinate = 
            Coordinate::builder().withRow(row).withColumn(column).build();
        isHit = games.at(playerNumber-1).isShipHit(targetCoordinate);

        if(gameType == GameType::Duo)
        {
            turn = 3 - turn;
        }
    }
    return prepareResultObject(isHit, playerNumber);
}

shootResultDTO battleshipGameEngine::shoot(int row, int col)
{
    return shoot(1, row, col);
}

shootResultDTO battleshipGameEngine::prepareResultObject(bool isHit, int playerNumber)
{
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

GameStats battleshipGameEngine::gameStats()
{
    return games.at(0).getGameStats();
}