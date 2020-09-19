#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <cmath>

class TextPresentationLayer
{
public:
    std::string const WELCOME_MESSAGE = 
        "Welcome to the Battleship Game Engine.\n";
    std::string const START_INSTRUCTION_MESSAGE = 
        "Type:\nstart           - to start new 8x8 game\nstart <int n>   - to start new nxn game\nexit            - to exit the application\n";
    std::string const GAME_START_MESSAGE = 
        "New game started - there are three ships:\nBATTLESHIP(4sq), CRUISER(3sq), DESTROYER(2sq)\n";
    std::string const ENTER_COORDINATES_MESSAGE = 
        "Enter target coordinates for the shot in the format:\n<row number> <column number>\n";
    std::string const CONGRATULATIONS_MESSAGE =
        "Congratulations, you sunked the last ship!!!\n";
    std::string const PLAY_AGAIN_MASSAGE = 
        "To play again type - \"play again\", to exit type anything else\n";
    std::string const BORDER = 
        "=========================================\n";

    TextPresentationLayer();
    ~TextPresentationLayer();
    std::string getTextPresentation(int gameboardSize);
    std::string getTextPresentation(std::vector<char> inputData);
    std::string getHitOrMissMessage(bool isHit);
private:
    std::string addGameboardHeader(int gameboardLen);
};