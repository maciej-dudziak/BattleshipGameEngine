#include "../battleshipGameEngine.hpp"

battleshipGameEngine::battleshipGameEngine()
{
}

battleshipGameEngine::~battleshipGameEngine()
{  
}

std::vector<bool> battleshipGameEngine::startGame()
{
    game.placeAllShips();
    return game.getGameboard();
}

std::vector<bool> battleshipGameEngine::startGame(int newGameboardSize)
{
    game.resizeGame(newGameboardSize);
    return startGame();
}

shootResultDTO battleshipGameEngine::shoot(int const row, int const column)
{
    auto targetCoordinate = 
        Coordinate::builder().withRow(row).withColumn(column).build();
    bool isHit = game.isShipHit(targetCoordinate);
    int shipCount = game.getShipCount();
    auto shipPlacement = game.getGameboard();
    auto hitsAndMisses = game.getHitsAndMisses();
    shootResultDTO result = shootResultDTO::builder().withIsHit(isHit)
                                                    .withShipPlacingVector(shipPlacement)
                                                    .withHitsAndMissesVector(hitsAndMisses)
                                                    .withShipsLeftCount(shipCount)
                                                    .build();

    return result;
}

GameStats battleshipGameEngine::gameStats()
{
    return game.getGameStats();
}