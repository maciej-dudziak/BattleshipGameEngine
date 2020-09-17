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
    if(response.starts_with("start"))
    {
        std::cout << textPresentationLayer.BORDER;
        std::cout << textPresentationLayer.GAME_START_MESSAGE;
        parseStartResponse(response);
        isGameStarted = true;
    }
    return isGameStarted;
}

bool TextPresentationController::promptUserToShoot()
{
    bool isShootFinal = false;
    std::cout << std::endl << textPresentationLayer.ENTER_COORDINATES_MESSAGE;

    std::string userInput;
    std::getline(std::cin, userInput);
    Coordinate target = parseShootInput(userInput);

    shootResultDTO shootResult = gameEngine.shoot(target.getRow(), target.getColumn());

    std::cout << std::endl << textPresentationLayer.getHitOrMissMessage(shootResult.getIsHit());
    std::cout << textPresentationLayer.getTextPresentation(shootResult.getHitsAnsMissesVector());
    if(shootResult.getShipsLeftCount() == 0)
    {
        isShootFinal = true;
    }
    return isShootFinal;
}

void TextPresentationController::parseStartResponse(std::string startResponse)
{
    if(startResponse == "start")
    {
        auto gamboard = gameEngine.startGame();
        std::cout << textPresentationLayer.getTextPresentation(gamboard.size());
    }
    else
    {
        int boardsizeArgument = parseBoardsizeArgument(startResponse);
        auto gameboard = gameEngine.startGame(boardsizeArgument);
        std::cout << textPresentationLayer.getTextPresentation(gameboard.size());
    }
    return;
}

int TextPresentationController::parseBoardsizeArgument(std::string response)
{
    auto delimiter = std::find(begin(response), end(response), ' ');
    int delimiterIndex = std::distance(begin(response), delimiter);
    std::string boardsizeArgument = response.substr(delimiterIndex++, std::string::npos);
    return std::stoi(boardsizeArgument);
}

Coordinate TextPresentationController::parseShootInput(std::string userInput)
{
    auto delimiter = std::find(begin(userInput), end(userInput), ' ');
    auto delimiterIndex = std::distance(begin(userInput), delimiter);

    std::string rowValue = userInput.substr(0,delimiterIndex--);
    int row = std::stoi(rowValue);

    std::string columnValue = userInput.substr(delimiterIndex++, std::string::npos);
    int column = std::stoi(columnValue);

    return Coordinate::builder().withRow(row).withColumn(column).build();
}