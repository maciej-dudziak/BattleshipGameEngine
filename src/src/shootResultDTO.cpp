#include "../shootResultDTO.hpp"

shootResultDTO::shootResultDTO(bool const _isHit, int const _shipsLeftCount,
        std::vector<bool> const _shipPlacingVector, std::vector<char> const _hitsAndMissesVector)
{
    isHit = _isHit;
    shipsLeftCount = _shipsLeftCount;
    shipPlacingVector = _shipPlacingVector;
    hitsAndMissesVector = _hitsAndMissesVector;
}

shootResultDTO::Builder::Builder()
{
}

shootResultDTO::Builder& shootResultDTO::Builder::withIsHit(bool const _isHit)
{
    isHit = _isHit;
    return *this;
}

shootResultDTO::Builder& shootResultDTO::Builder::withShipsLeftCount(int const _shipsLeftCount)
{
    shipsLeftCount = _shipsLeftCount;
    return *this;
}

shootResultDTO::Builder& shootResultDTO::Builder::withShipPlacingVector(std::vector<bool> const _shipPlacingVector)
{
    shipPlacingVector = _shipPlacingVector;
    return *this;
}

shootResultDTO::Builder& shootResultDTO::Builder::withHitsAndMissesVector(std::vector<char> const _hitsAndMissesVector)
{
    hitsAndMissesVector = _hitsAndMissesVector;
    return *this;
}

shootResultDTO shootResultDTO::Builder::build()
{
    return shootResultDTO(isHit, shipsLeftCount, shipPlacingVector, hitsAndMissesVector);
}

shootResultDTO::Builder shootResultDTO::builder()
{
    return Builder();
}