#include "catch.hpp"
#include "../src/battleshipGame.hpp"

SCENARIO("Default construction of the Battleship Game")
{
    GIVEN("The battleshipGame object is created")
    {
        WHEN("The constructor is invoked without any arguments")
        {
            battleshipGame game = battleshipGame();
            auto gameboard = game.getGameboard();
            THEN("The default gameboard size is 8x8")
            {
                REQUIRE(64 == gameboard.size());
            }
        }
    }
}

SCENARIO("Placing all the ships randomly")
{
    GIVEN("A battleshipGame is created")
    {
        battleshipGame game = battleshipGame();
        WHEN("placeAllShips() method is called")
        {
            game.placeAllShips();
            THEN("Total number of set fields is 9")
            {
                auto gameboard = game.getGameboard();
                int numberOfSetFields = std::count(begin(gameboard), end(gameboard), true);
                REQUIRE(9 == numberOfSetFields);
            }
            THEN("Number of restricted fields is at least 24")
            {
                auto restricted = game.getRestrictedFields();
                int numberOfRestrictedFields = std::count(begin(restricted), end(restricted), true);
                REQUIRE(24 <= numberOfRestrictedFields);
            }
        }
    }
}

SCENARIO("Checking if the ship is hit")
{
    GIVEN("A battleshipGame object is created")
    {
        battleshipGame game = battleshipGame();
        WHEN("Ships are not placed yet")
        {
            THEN("For a random coordinate battleshipGame::isShipHit() returns false")
            {
                RandomEngine randomEngine = RandomEngine();
                int row = randomEngine.getRandomInt(0,7);
                int col = randomEngine.getRandomInt(0,7);
                Coordinate coord = Coordinate::builder().withRow(row).withColumn(col).build();
                bool res = game.isShipHit(coord);
                REQUIRE_FALSE(res);
            }
        }
        WHEN("Ships are placed")
        {
            game.placeAllShips();
            auto gameboard = game.getGameboard();
            THEN("For targeting a ship battleshipGame::isShipHit() returns true")
            {
                auto shipField = std::find(begin(gameboard), end(gameboard), true);
                int shipFieldIndex = shipField - begin(gameboard);
                int row = shipFieldIndex/8 + 1;
                int col = shipFieldIndex%8 + 1;
                Coordinate coord = Coordinate::builder().withRow(row).withColumn(col).build();
                bool res = game.isShipHit(coord);
                REQUIRE_FALSE(!res);
            }
        }
    }
}