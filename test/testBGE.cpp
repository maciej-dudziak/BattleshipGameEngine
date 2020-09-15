#include "catch.hpp"
#include "../src/battleshipGameEngine.h"

SCENARIO("battleshipGameEngine::startGame() should begin a 1-player game")
{
    GIVEN("A battleshipGameEngine object is created")
    {
        battleshipGameEngine gameEngine = battleshipGameEngine();
        WHEN("The startGame() method is called")
        {
            auto placingArray = gameEngine.startGame();
            THEN("A ship placing array is returned with three ships placed randomly")
            {
                int setFieldsCount = std::count(begin(placingArray), end(placingArray), true);
                REQUIRE(9 == setFieldsCount);
            }
        }
    }
}

SCENARIO("battleshipGameEngine::shoot(row, column) should target represented cell and",
"and return information about hit or miss, number of ships left, the ship placement array and hits/misses array")
{
    battleshipGameEngine gameEngine = battleshipGameEngine();
    GIVEN("battleshipEngineObject is created but ships are not placed yet")
    {
        WHEN("battleshipGameEngine::shoot() method is called with target row and column arguments")
        {
            auto res = gameEngine.shoot(1, 1);
            THEN("Information about miss is returned")
            {
                REQUIRE_FALSE(res.getIsHit());
            }
            THEN("The number of ships left is returned and is equal to zero")
            {
                int shipsCount = res.getShipsLeftCount();
                REQUIRE(0 == shipsCount);
            }
            THEN("The empty ship placement array is returned")
            {
                auto shipPlacement = res.getShipPlacingVector();
                REQUIRE(std::vector<bool>(64,false) == shipPlacement);
            }
            THEN("Hits/misses array is returned")
            {
                auto hitsAndMisses = res.getHitsAnsMissesVector();
                REQUIRE('X' == hitsAndMisses[0]);
                REQUIRE(' ' == hitsAndMisses[5]);
            }
        }
    }
}