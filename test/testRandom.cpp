#include "catch.hpp"
#include "../src/random.hpp"

SCENARIO("Random function returs a random number in specified range")
{
    GIVEN("Random engine is created and minimum and maximum values are known")
    {
        RandomEngine randomEngine = RandomEngine();
        int min = 0;
        int max = 63;
        WHEN("The random function is called")
        {
            int generatedRandomInt = randomEngine.getRandomInt(min, max);
            THEN("Random integer from the specified range is returned")
            {
                REQUIRE(0 <= generatedRandomInt);
                REQUIRE(63 >= generatedRandomInt);
            }
        }
        WHEN("The function is called three times")
        {
            int firstInt = randomEngine.getRandomInt(min, max);
            int secondInt = randomEngine.getRandomInt(min, max);
            int thirdInt = randomEngine.getRandomInt(min, max);
            THEN("At least one number is different")
            {
                bool areAllThreeEqual = (firstInt == secondInt) && (firstInt == thirdInt);
                REQUIRE_FALSE(areAllThreeEqual);
            }
        }
    }
}