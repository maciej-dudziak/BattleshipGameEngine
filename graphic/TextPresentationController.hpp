#include "TextPresentationLayer.hpp"
#include "../src/battleshipGameEngine.hpp"
#include <iostream>
#include <sstream>

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
    
    bool carryStartGameSequence();
    bool carryTurnSequence();
private:
    bool carryShootSequence(std::string inputCoordinates);

    bool parseStartResponse(std::string userInput);
    bool parseGamemodeArgument(std::string userInput);
    int parseBoardsizeArgument(std::string userInput);
    int parsePlayerNumber(std::vector<std::string> commandWords);
    Coordinate parseShootInput(std::string inputCoordinates);

    bool areStatsRequested(std::string userInput);
    bool isStartRequested(std::string userInput);
    bool isGamemodeSpecified(std::string userInput);

    std::string promptUserToStartGame();
    std::string promptUserToEnterCoordinates();

    std::vector<std::string> splitIntoWords(std::string input);   
};