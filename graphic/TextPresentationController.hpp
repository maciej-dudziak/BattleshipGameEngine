#include "TextPresentationLayer.hpp"
#include "../src/battleshipGameEngine.hpp"
#include <iostream>

class TextPresentationController
{
private:
    TextPresentationLayer textPresentationLayer;
    battleshipGameEngine gameEngine;
public:
    TextPresentationController();
    ~TextPresentationController();
    std::string getWelcomeMessage() {return textPresentationLayer.WELCOME_MESSAGE;};
    std::string getCongratulationsMessage() {return textPresentationLayer.CONGRATULATIONS_MESSAGE;}
    
    bool promptUserToStartAGame();
    bool promptUserToShoot();
private:
    void parseStartResponse(std::string response);
    int parseBoardsizeArgument(std::string response);
    Coordinate parseShootInput(std::string inputCoordinates);
};