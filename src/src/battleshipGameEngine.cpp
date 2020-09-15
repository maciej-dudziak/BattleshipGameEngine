#include "../battleshipGameEngine.h"

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

shootResultDTO battleshipGameEngine::shoot(int const row, int const column)
{
    auto targetCoordinate = 
        Coordinate::builder().withRow(row).withColumn(column).build();
    bool isHit = game.isShipHit(targetCoordinate);

    auto shipPlacement = game.getGameboard();
    auto hitsAndMisses = game.getHitsAndMisses();
    shootResultDTO result = shootResultDTO::builder().withIsHit(isHit)
                                                    .withShipPlacingVector(shipPlacement)
                                                    .withHitsAndMissesVector(hitsAndMisses)
                                                    .build();

    return result;
}