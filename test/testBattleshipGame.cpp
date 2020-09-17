#include "catch.hpp"
#include "../src/battleshipGame.hpp"
#include <algorithm>

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

SCENARIO("Resizing a gameboard using the battleshipGame::resizeGameboard(int) method")
{
    GIVEN("The battleshipGame object is created")
    {
        battleshipGame game = battleshipGame();
        WHEN("batttleshipGame::resizeGameboard(10) method is called - gameboard extended")
        {
            game.resizeGame(10);
            auto gameboard = game.getGameboard();
            auto restricted = game.getRestrictedFields();
            auto hitsMisses = game.getHitsAndMisses();
            THEN("Gameboard size is changed to 10x10")
            {
                REQUIRE(100 == gameboard.size());
                REQUIRE(100 == restricted.size());
                REQUIRE(100 == hitsMisses.size());
            }
            THEN("Correct initialisation is maintained")
            {
                auto firstTrue = std::find(begin(gameboard), end(gameboard), true);
                auto firstNotSpaceChar = std::find_if_not(begin(hitsMisses), end(hitsMisses), [](char character) { return character == ' ';});
                REQUIRE(end(gameboard) == firstTrue);
                REQUIRE(end(hitsMisses) == firstNotSpaceChar);
            }
        }
        WHEN("batttleshipGame::resizeGameboard(10) method is called - gameboard reduced")
        {
            game.resizeGame(6);
            auto gameboard = game.getGameboard();
            auto restricted = game.getRestrictedFields();
            auto hitsMisses = game.getHitsAndMisses();
            THEN("Gameboard size is changed to 6x6")
            {
                REQUIRE(36 == gameboard.size());
                REQUIRE(36 == restricted.size());
                REQUIRE(36 == hitsMisses.size());
            }
            THEN("Correct initialisation is maintained")
            {
                auto firstTrue = std::find(begin(gameboard), end(gameboard), true);
                auto firstNotSpaceChar = std::find_if_not(begin(hitsMisses), end(hitsMisses), [](char character) { return character == ' ';});
                REQUIRE(end(gameboard) == firstTrue);
                REQUIRE(end(hitsMisses) == firstNotSpaceChar);
            }
        }
    }
}