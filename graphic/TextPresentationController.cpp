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
    try
    {
        if(areStatsRequested(userInput))
        {
            std::string statsResponse = getRequestedStats(userInput);
            std::cout << statsResponse << std::endl;
        }
        else if(isResignRequested(userInput))
        {
            gameEnd = true;
        }
        else
        {
            gameEnd = carryShootSequence(userInput);
            if(gameEnd)
            {
                std::cout << std::endl << getCongratulationsMessage();
            }
        }
    } catch (std::invalid_argument& e) {
            std::cout << "Invalid input! Please follow strictly given commands and format.\n";
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

std::string TextPresentationController::getRequestedStats(std::string userInput)
{
    auto commandWords = splitIntoWords(userInput);
    std::string output;
    if(commandWords.size() == 1)
    {
        output = gameEngine.gameStats().to_string();
    }
    else if(commandWords.size() == 2)
    {
        int playerNumber = std::stoi(commandWords.at(1));
        output = gameEngine.gameStats(playerNumber).to_string();
    }
    return output;
}

bool TextPresentationController::carryShootSequence(std::string inputCoordinates)
{
    auto commandWords = splitIntoWords(inputCoordinates);
    bool allShipsDestroyed = false;
    
    int playerNumber;
    int row;
    int column;

    if(commandWords.size() < 2) throw std::invalid_argument(" ");
    playerNumber = parsePlayerNumber(commandWords);
    row = std::stoi(commandWords.at(0));
    column = std::stoi(commandWords.at(1));
    
    shootResultDTO shootResult = gameEngine.shoot(row, column, playerNumber);

    std::cout << textPresentationLayer.BORDER;
    std::cout << textPresentationLayer.getResultMessage(shootResult.getIsHit(), playerNumber);
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

bool TextPresentationController::isResignRequested(std::string userInput)
{
    return userInput.starts_with("resign");
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
    if(gameEngine.getGameType() == GameType::Duo) std::cout << textPresentationLayer.PLAYER_NUMBER_MESSAGE;
    std::cout << std::endl;
    
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
    if(gameEngine.getGameType() == GameType::Single)
    {
        return 1;
    }
    if(commandWords.size() < 3)
    {
        throw std::invalid_argument("not enough arguments");
    }
    int playerNumber = std::stoi(commandWords.at(2));
    if(playerNumber != 1 && playerNumber != 2)
    {
        throw std::invalid_argument("wrong player number, values allowed - 1 or 2");
    }
    return playerNumber;
}