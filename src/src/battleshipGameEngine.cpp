#include "../battleshipGameEngine.hpp"
#include <iostream>
battleshipGameEngine::battleshipGameEngine()
{
}

battleshipGameEngine::~battleshipGameEngine()
{  
}

std::vector<bool> battleshipGameEngine::startGame()
{
    resetGames();
    turn = 1;
    gameType = GameType::Single;
    games.push_back(battleshipGame());
    games[0].placeAllShips();
    return games[0].getGameboard();
}

std::vector<bool> battleshipGameEngine::startGame(int gameboardSize)
{
    if(gameboardSize < 6)
    {
        throw std::invalid_argument("Gameboard size can't be smaller than 6!");
    }
    resetGames();
    turn = 1;
    gameType = GameType::Single;
    games.push_back(battleshipGame(gameboardSize));
    games[0].placeAllShips();
    return games[0].getGameboard();
}

std::vector<bool> battleshipGameEngine::startGame(bool twoPlayers)
{
    startGame();
    if(twoPlayers)
    {
        gameType = GameType::Duo;
        games.push_back(battleshipGame());
        games[1].placeAllShips();
    }
    return games[0].getGameboard();
}

std::vector<bool> battleshipGameEngine::startGame(bool twoPlayers, int gameboardSize)
{
    startGame(gameboardSize);
    if(twoPlayers)
    {
        gameType = GameType::Duo;
        games.push_back(battleshipGame(gameboardSize));
        games[1].placeAllShips();
    }
    return games[0].getGameboard();
}

shootResultDTO battleshipGameEngine::shoot(int row, int column, int playerNumber)
{
    bool isHit = false;
    if(turn == playerNumber)
    {
        auto targetCoordinate = 
            Coordinate::builder().withRow(row).withColumn(column).build();
        bool notShootYet = games.at(playerNumber-1).canBeShoot(targetCoordinate);
        isHit = games.at(playerNumber-1).isShipHit(targetCoordinate);

        if(gameType == GameType::Duo && notShootYet)
        {
            turn = changeTurn(turn);
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

void battleshipGameEngine::resetGames()
{
    games = std::vector<battleshipGame>();
}

int battleshipGameEngine::changeTurn(int previousTurn)
{
    return 3 - previousTurn;
}