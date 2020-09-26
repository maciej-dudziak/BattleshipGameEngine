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
        "Type:\n"
        "start                or\n"
        "start single       - to start new 8x8 single game\n"
        "start duo          - to start new 8x8 two players game\n"
        "start <int n>      - to start new nxn single game with n>5\n"
        "start <int n> duo  - to start new nxn two players game with n>5\n"
        "stats              - at any point in the game to see game statistics\n"
        "resign             - to end the ongoing game\n"
        "exit               - to exit the application\n";
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
    std::string const GAME_STATS_MESSAGE = 
        "Current game stats:\n";

    TextPresentationLayer();
    ~TextPresentationLayer();
    std::string getTextPresentation(int gameboardSize, bool twoPlayers);
    std::string getTextPresentation(std::vector<char> inputData);
    std::string getResultMessage(bool isHit, int playerNumber);
    std::string getTurnMessage(int playerNumber);
private:
    std::string addGameboardHeader(int gameboardLen);
};