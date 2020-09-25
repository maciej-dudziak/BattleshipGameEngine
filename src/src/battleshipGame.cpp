#include "../battleshipGame.hpp"

battleshipGame::battleshipGame()
{
    boardsize = DEFAULT_BOARD_SIZE;
    gameboard = std::vector<bool>(boardsize*boardsize, false);
    restrictedFields = std::vector<bool>(boardsize*boardsize, false);
    hitsAndMisses = std::vector<char>(boardsize*boardsize, ' ');
}

battleshipGame::~battleshipGame()
{
}

void battleshipGame::resizeGame(int newGameboardSize)
{
    if(newGameboardSize < 6)
    {
        return;
    }
    boardsize = newGameboardSize;
    gameboard.resize(newGameboardSize*newGameboardSize, false);
    restrictedFields.resize(newGameboardSize*newGameboardSize, false);
    hitsAndMisses.resize(newGameboardSize*newGameboardSize, ' ');
}

void battleshipGame::placeAllShips()
{
    std::vector<int> battleshipPlacing = placeShip(BATTLESHIP_LEN);
    ships.push_back(Ship(battleshipPlacing));

    std::vector<int> destroyerPlacing;
    do {
        destroyerPlacing = placeShip(DESTROYER_LEN);
    } while(destroyerPlacing.size() == 0);
    ships.push_back(Ship(destroyerPlacing));

    std::vector<int> cruiserPlacing;
    do {
        cruiserPlacing = placeShip(CRUISER_LEN);
    } while(cruiserPlacing.size() == 0);
    ships.push_back(Ship(cruiserPlacing));

    return;
}

bool battleshipGame::isShipHit(Coordinate coord)
{
    if(!validateCoord(coord))
    {
        return false;
    }
    int gameboardIndex = convertToGameboardIndex(coord);
    bool result = gameboard.at(gameboardIndex);

    updateGameStatus(gameboardIndex, result);
    updateGameStats(result);
    return result;
}

void battleshipGame::updateGameStats(bool shootResult)
{
    gameStats.addPlayedTurn();
    if(shootResult) gameStats.addHit();
    else gameStats.addMiss();
}

void battleshipGame::updateGameStatus(int index, bool isHit)
{
    updateHitsAndMisses(index, isHit);
    if(isHit)
    {
        updateShipCount(index);
    }
}

std::vector<int> battleshipGame::placeShip(int shipLen)
{
    Direction battleshipDirection = getDirection();
    auto occupiedIndexes = std::vector<int>();
    switch (battleshipDirection)
    {
        case Direction::Right:
            occupiedIndexes = placeShipRightwards(shipLen);
            break;
    
        case Direction::Down:
            occupiedIndexes = placeShipDownwards(shipLen);
            break;
    }
    return occupiedIndexes;
}

std::vector<int> battleshipGame::placeShipRightwards(const int shipLen)
{
    int rangeMax = boardsize * (boardsize - shipLen + 1) - 1;
    int shipCenter = randomEngine.getRandomInt(0, rangeMax);
    int realGameboardIndex = getRealIndexWhenPlacingRightwards(shipCenter, shipLen);

    if(!validateFieldsRightwards(realGameboardIndex, shipLen))
    {
        return std::vector<int>();
    }
    auto occupiedIndexes = setOccupationRightwards(realGameboardIndex, shipLen);
    setRestrictedRightwards(realGameboardIndex, shipLen);
    return occupiedIndexes;
}

std::vector<int> battleshipGame::placeShipDownwards(const int shipLen)
{
    int rangeMax = (boardsize * (boardsize - shipLen + 1)) - 1;
    int shipCenter = randomEngine.getRandomInt(0, rangeMax);

    if(!validateFieldsDownwards(shipCenter, shipLen))
    {
        return std::vector<int>();
    }
    auto occupiedIndexes = setOccupationDownwards(shipCenter, shipLen);
    setRestrictedDownwards(shipCenter, shipLen);
    return occupiedIndexes;
}

Direction battleshipGame::getDirection()
{
    return randomEngine.getRandomInt(0,1) ? Direction::Right : Direction::Down;
}

const bool battleshipGame::isOccupied(int index)
{
    return gameboard.at(index);
}

const bool battleshipGame::isRestricted(int index)
{
    return restrictedFields.at(index);
}

int battleshipGame::getRealIndexWhenPlacingRightwards(int index, int shipLen)
{
    int rowNumber = index / (boardsize - shipLen + 1);
    int realIndex = index + rowNumber * (shipLen - 1);
    return realIndex;
}

bool const battleshipGame::validateFieldsRightwards(int startingIndex, int shipLen)
{
    for (int i = 0;  i < shipLen; i++)
    {
        if (isOccupied(startingIndex+i) || isRestricted(startingIndex+i))
        {
            return false;
        }
    }
    return true;
}

bool const battleshipGame::validateFieldsDownwards(int startingIndex, int shipLen)
{
    for (int i = 0; i < shipLen; i++)
    {
        int offset = i*boardsize;
        if (isOccupied(startingIndex+offset) || isRestricted(startingIndex+offset))
        {
            return false;
        }
    }
    return true;
}

std::vector<int> battleshipGame::setOccupationRightwards(int start, int len)
{
    std::vector<int> occupiedIndexes = std::vector<int>();
    for (int i = 0; i < len; i++)
    {
        gameboard.at(start+i) = true;
        occupiedIndexes.push_back(start+i);
    }
    return occupiedIndexes;
}

std::vector<int> battleshipGame::setOccupationDownwards(int start, int len)
{
    std::vector<int> occupiedIndexes = std::vector<int>();
    for (int i = 0; i < len; i++)
    {
        int offset = i*boardsize;
        gameboard.at(start+offset) = true;
        occupiedIndexes.push_back(start+offset);
    }
    return occupiedIndexes;
}

void battleshipGame::setRestrictedRightwards(int start, int len)
{
    bool isLeftBorder = start%boardsize == 0;
    bool isRightBorder = (start+len)%boardsize == 0;
    bool isTopBorder = start/boardsize == 0;
    bool isBottomBorder = start/boardsize == (boardsize-1);

    if (!isLeftBorder)
    {
        restrictedFields.at(start-1) = true;
    }
    if (!isRightBorder)
    {
        restrictedFields.at(start+len) = true;
    }
    if (!isTopBorder)
    {
        for (int i = 0; i < len; i++)
        {
            restrictedFields.at(start-boardsize+i) = true;
        }
    }
    if (!isBottomBorder)
    {
        for (int i = 0; i < len; i++)
        {
            restrictedFields.at(start+boardsize+i) = true;
        }
    }
    if (!(isLeftBorder || isTopBorder))
    {
        restrictedFields.at(start-boardsize-1) = true;
    }
    if (!(isRightBorder || isTopBorder))
    {
        restrictedFields.at(start-boardsize+len) = true;
    }
    if (!(isLeftBorder || isBottomBorder))
    {
        restrictedFields.at(start+boardsize-1) = true;
    }
    if (!(isRightBorder || isBottomBorder))
    {
        restrictedFields.at(start+boardsize+len) = true;
    }
}

void battleshipGame::setRestrictedDownwards(int start, int len)
{
    bool isLeftBorder = start%boardsize == 0;
    bool isRightBorder = start%boardsize == (boardsize-1);
    bool isTopBorder = start/boardsize == 0;
    bool isBottomBorder = (start+len*boardsize) > (boardsize*boardsize - 1);

    if (!isLeftBorder)
    {
        for (int i = 0; i < len; i++)
        {
            int offset = i*boardsize - 1;
            restrictedFields.at(start + offset) = true;
        }
    }
    if (!isRightBorder)
    {
        for (int i = 0; i < len; i++)
        {
            int offset = i*boardsize + 1;
            restrictedFields.at(start + offset) = true;
        }
    }
    if (!isTopBorder)
    {
        restrictedFields.at(start-boardsize) = true;
    }
    if (!isBottomBorder)
    {
        int offset = boardsize*len;
        restrictedFields.at(start+offset) = true;
    }
    if (!(isLeftBorder || isTopBorder))
    {
        restrictedFields.at(start-boardsize-1) = true;
    }
    if (!(isRightBorder || isTopBorder))
    {
        restrictedFields.at(start-boardsize+1) = true;
    }
    if (!(isLeftBorder || isBottomBorder))
    {
        int offset = len*boardsize - 1;
        restrictedFields.at(start+offset) = true;
    }
    if (!(isRightBorder || isBottomBorder))
    {
        int offset = len*boardsize + 1;
        restrictedFields.at(start+offset) = true;
    }
}

int battleshipGame::convertToGameboardIndex(Coordinate coord)
{
    return (coord.getRow()-1)*boardsize + (coord.getColumn()-1);
}

void battleshipGame::updateHitsAndMisses(int index, bool isHit)
{
    hitsAndMisses.at(index) = isHit ? '0' : 'X';
}

void battleshipGame::updateShipCount(int index)
{
    for(auto i = begin(ships); i < end(ships); i++)
    {
        if(i->removeIfFound(index))
        {
            int noOfOccupiedFields = i->getNumberOfOccupiedFields();
            if(noOfOccupiedFields == 0)
            {
                ships.erase(i);
                break;
            }
        }
    }
}

bool const battleshipGame::validateCoord(Coordinate coord)
{
    return (coord.getRow() > 0 && coord.getRow() < (boardsize+1) && coord.getColumn() > 0 && coord.getColumn() < (boardsize+1));
}