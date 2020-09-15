#include "catch.hpp"
#include "../src/shootResultDTO.h"

SCENARIO("Building a shootResultDTO")
{
    GIVEN("All the parameters are provided")
    {
        bool isHit = true;
        int shipsLeftCount = 6;
        std::vector<bool> shipPlacement = std::vector<bool>(4, true);
        std::vector<char> hits = std::vector<char> {'a', 'b'};
        WHEN("The DTO object is build")
        {
            auto dto = shootResultDTO::builder().withIsHit(isHit)
                                                .withShipsLeftCount(shipsLeftCount)
                                                .withShipPlacingVector(shipPlacement)
                                                .withHitsAndMissesVector(hits)
                                                .build();
            THEN("A DTO object with corresponding values is created")
            {
                REQUIRE(isHit == dto.getIsHit());
                REQUIRE(shipsLeftCount == dto.getShipsLeftCount());
                REQUIRE(shipPlacement == dto.getShipPlacingVector());
                REQUIRE(hits == dto.getHitsAnsMissesVector());
            }
        }
    }
}   