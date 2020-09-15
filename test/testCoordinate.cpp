#include "catch.hpp"
#include "../src/Coordinate.h"

SCENARIO("Building a Coordinate object")
{
    GIVEN("Row and column values")
    {
        int row = 5;
        int column = 1;
        WHEN("When Coordinate build procedure is executed")
        {
            auto coordinate = Coordinate::builder().withRow(row).withColumn(column).build();
            THEN("A coordinate object with corresponding values for row and column is created")
            {
                REQUIRE(row == coordinate.getRow());
                REQUIRE(column == coordinate.getColumn());
            }
        }
    }
}