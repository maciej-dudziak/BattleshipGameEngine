#pragma once
#include <vector>
#include "Coordinate.hpp"
#include "shootResultDTO.hpp"
#include "battleshipGame.hpp"

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