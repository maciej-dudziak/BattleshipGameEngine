#include "TextPresentationController.hpp"

TextPresentationController::TextPresentationController()
{
}

TextPresentationController::~TextPresentationController()
{
}

/*
1) Startuje Aplikacja -> some welcome information
2) 
*/

bool TextPresentationController::promptUserToStartAGame()
{
    std::cout << textPresentationLayer.START_INSTRUCTION_MESSAGE;
    bool isGameStarted = false;

    std::string response;
    std::getline(std::cin, response);
    if(isStartRequested(response))
    {
        std::cout << textPresentationLayer.BORDER;
        std::cout << textPresentationLayer.GAME_START_MESSAGE;
        isGameStarted = parseStartResponse(response);
    }
    return isGameStarted;
}

bool TextPresentationController::promptUserToShoot()
{
    std::cout << std::endl << textPresentationLayer.ENTER_COORDINATES_MESSAGE;
    bool isShootFinal = false;

    std::string userInput;
    std::getline(std::cin, userInput);

    if(areStatsRequested(userInput))
    {
        std::cout << gameEngine.gameStats().to_string();
        return false;
    }
    try {
        Coordinate target = parseShootInput(userInput);

        shootResultDTO shootResult = gameEngine.shoot(target.getRow(), target.getColumn());

        std::cout << std::endl << textPresentationLayer.getHitOrMissMessage(shootResult.getIsHit());
        std::cout << textPresentationLayer.getTextPresentation(shootResult.getHitsAnsMissesVector());
        if(shootResult.getShipsLeftCount() == 0)
        {
            isShootFinal = true;
        }
    } catch (std::invalid_argument)
    {
        std::cout << "Invalid coordinates! Please follow strictly given format\n";
    }
    return isShootFinal;
}

bool TextPresentationController::parseStartResponse(std::string startResponse)
{
    std::istringstream iss(startResponse);
    std::vector<std::string> commandWords {std::istream_iterator<std::string>(iss), {}};
    std::vector<bool> gameboard;

    if(commandWords.size() == 1)
    {
        gameboard = gameEngine.startGame();
    }
    else if(commandWords.size() == 2)
    {
        if(isGamemodeSpecified(commandWords.at(1)))
        {
            bool isDuoGameRequested = parseGamemodeArgument(commandWords.at(1));
            gameboard = gameEngine.startGame(isDuoGameRequested);
        }
        else
        {        
            int boardsizeArgument = parseBoardsizeArgument(commandWords.at(1));
            gameboard = gameEngine.startGame(boardsizeArgument);
        }
    }
    std::cout << textPresentationLayer.getTextPresentation(gameboard.size());
    return true;
}

int TextPresentationController::parseBoardsizeArgument(std::string argument)
{
    return std::stoi(argument);
}

Coordinate TextPresentationController::parseShootInput(std::string userInput)
{
    auto delimiter = std::find(begin(userInput), end(userInput), ' ');
    auto delimiterIndex = std::distance(begin(userInput), delimiter);

    std::string rowValue = userInput.substr(0,delimiterIndex);
    int row = std::stoi(rowValue);

    std::string columnValue = userInput.substr(delimiterIndex+1, std::string::npos);
    int column = std::stoi(columnValue);

    return Coordinate::builder().withRow(row).withColumn(column).build();
}

bool TextPresentationController::areStatsRequested(std::string userInput)
{
    return userInput.starts_with("stats");
}

bool TextPresentationController::isStartRequested(std::string userInput)
{
    return userInput.starts_with("start");
}

bool TextPresentationController::isGamemodeSpecified(std::string userInput)
{
    return userInput == "single" || userInput == "duo";
}

bool TextPresentationController::parseGamemodeArgument(std::string userInput)
{
    return userInput == "duo";
}