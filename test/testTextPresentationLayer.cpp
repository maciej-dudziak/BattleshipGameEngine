#include "catch.hpp"
#include "../graphic/TextPresentationLayer.hpp"

SCENARIO("Printing a text representation of a nxn game array")
{
    TextPresentationLayer textPresentationLayer = TextPresentationLayer();
    GIVEN("The parameter n equal to 4 is provided")
    {
        int n = 4;
        WHEN("TextPresentationLayer::getTextPresentation(n) is called")
        {
            std::string output = textPresentationLayer.getTextPresentation(n*n);
            THEN("An empty representation layer is returned")
            {
                std::string expected = 
                    std::string(" 1 2 3 4\n1       \n2       \n3       \n4       ");
                REQUIRE(expected == output);
            }
        }
    }
    GIVEN("The hits and misses vector is provided")
    {
        std::vector<char> hitsMisses = std::vector<char>(16, '0');
        WHEN("TextPresentationLayer::getTextPresentation(hitsMisses) is called")
        {
            std::string output = textPresentationLayer.getTextPresentation(hitsMisses);
            THEN("An 0-filled representation layer is returned")
            {
                std::string expected = 
                    std::string(" 1 2 3 4\n1 0 0 0 0\n2 0 0 0 0\n3 0 0 0 0\n4 0 0 0 0");
                REQUIRE(expected == output);
            }
        }
    }
}