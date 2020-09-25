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

bool TextPresentationController::carryStartGameSequence()
{
    bool isGameStarted = false;
    std::string response = promptUserToStartGame();
    if(isStartRequested(response))
    {
        std::cout << textPresentationLayer.BORDER;
        std::cout << textPresentationLayer.GAME_START_MESSAGE;
        isGameStarted = parseStartResponse(response);
    }
    return isGameStarted;
}

bool TextPresentationController::carryTurnSequence()
{
    bool gameEnd = false;
    std::cout << std::endl << textPresentationLayer.BORDER;
    std::cout << textPresentationLayer.getTurnMessage(gameEngine.getCurrentTurn());
    std::string userInput = promptUserToEnterCoordinates();

    if(areStatsRequested(userInput))
    {
        std::cout << gameEngine.gameStats().to_string();
    }
    else
    {
        gameEnd = carryShootSequence(userInput);
    }
    return gameEnd;
}

bool TextPresentationController::parseStartResponse(std::string startResponse)
{
    auto commandWords = splitIntoWords(startResponse);
    std::vector<bool> gameboard;
    bool duoGame = false;
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
            duoGame = isDuoGameRequested;
        }
        else
        {        
            int boardsizeArgument = parseBoardsizeArgument(commandWords.at(1));
            gameboard = gameEngine.startGame(boardsizeArgument);
        }
    }
    else if(commandWords.size() == 3)
    {
        bool isDuoGameRequested = parseGamemodeArgument(commandWords.at(1));
        int boardsizeArgument = parseBoardsizeArgument(commandWords.at(2));
        gameboard = gameEngine.startGame(isDuoGameRequested, boardsizeArgument);
        duoGame = isDuoGameRequested;
    }
    std::cout << textPresentationLayer.getTextPresentation(gameboard.size(), duoGame);
    return true;
}

int TextPresentationController::parseBoardsizeArgument(std::string argument)
{
    return std::stoi(argument);
}

bool TextPresentationController::carryShootSequence(std::string inputCoordinates)
{
    auto commandWords = splitIntoWords(inputCoordinates);
    bool allShipsDestroyed = false;
    
    int playerNumber;
    int row;
    int column;
    try {
        playerNumber = parsePlayerNumber(commandWords);
        if(commandWords.size() < 2) throw std::invalid_argument("not enough arguments");
        row = std::stoi(commandWords.at(0));
        column = std::stoi(commandWords.at(1));
    } catch (std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "! Please follow strictly given format\n";
            return allShipsDestroyed;
    }
    shootResultDTO shootResult = gameEngine.shoot(row, column, playerNumber);

    std::cout << textPresentationLayer.BORDER;
    std::cout << textPresentationLayer.getHitOrMissMessage(shootResult.getIsHit());
    std::cout << textPresentationLayer.getTextPresentation(shootResult.getHitsAnsMissesVector());
        
    allShipsDestroyed = (0 == shootResult.getShipsLeftCount());
    return allShipsDestroyed;
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

std::string TextPresentationController::promptUserToStartGame()
{
    std::cout << textPresentationLayer.START_INSTRUCTION_MESSAGE;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

std::string TextPresentationController::promptUserToEnterCoordinates()
{
    std::cout << textPresentationLayer.ENTER_COORDINATES_MESSAGE;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

std::vector<std::string> TextPresentationController::splitIntoWords(std::string input)
{
    std::istringstream iss(input);
    return {std::istream_iterator<std::string>(iss), {}};
}

int TextPresentationController::parsePlayerNumber(std::vector<std::string> commandWords)
{
    if (commandWords.size() < 3)
    {
        return 1;
    }
    int playerNumber = std::stoi(commandWords.at(2));
    if(playerNumber != 1 && playerNumber != 2)
    {
        throw std::invalid_argument("wrong player number, values allowed - 1 or 2");
    }
    return playerNumber;
}