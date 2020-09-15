#pragma once
#include <vector>
#include "Coordinate.h"
#include "shootResultDTO.h"
#include "battleshipGame.h"

class battleshipGameEngine
{
private:
    battleshipGame game = battleshipGame();
public:
    battleshipGameEngine();
    ~battleshipGameEngine();

    std::vector<bool> startGame();
    shootResultDTO shoot(int row, int col);
};