#include <vector>

class shootResultDTO
{
private:
    bool isHit;
    int shipsLeftCount;
    std::vector<bool> shipPlacingVector;
    std::vector<char> hitsAndMissesVector;

    class Builder
    {
    private:
        bool isHit;
        int shipsLeftCount;
        std::vector<bool> shipPlacingVector;
        std::vector<char> hitsAndMissesVector;
    public:
        Builder();
        Builder& withIsHit(bool const _isHit);
        Builder& withShipsLeftCount(int const _shipsLeftCount);
        Builder& withShipPlacingVector(std::vector<bool> const _shipPlacingVector);
        Builder& withHitsAndMissesVector(std::vector<char> const _hitsAndMissesVector);
        shootResultDTO build();
    };

public:
    bool const getIsHit() { return isHit; }
    int const getShipsLeftCount() { return shipsLeftCount; }
    std::vector<bool> getShipPlacingVector() { return shipPlacingVector; }
    std::vector<char> getHitsAnsMissesVector() { return hitsAndMissesVector; }
    static Builder builder();

private:
    shootResultDTO(bool const _isHit, int const _shipsLeftCount,
        std::vector<bool> const _shipPlacingVector, std::vector<char> const _hitsAndMissesVector);
};