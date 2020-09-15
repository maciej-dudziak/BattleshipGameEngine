#pragma once
#include <vector>
#include "random.h"
#include "Coordinate.h"

enum class Direction 
{
    Right,
    Down
};

class battleshipGame
{
    private:
        int const DEFAULT_BOARD_SIZE = 8;
        int const BATTLESHIP_LEN = 4;
        int const DESTROYER_LEN = 3;
        int const CRUISER_LEN = 2;

        int boardsize;
        std::vector<bool> gameboard;
        std::vector<bool> restrictedFields;
        std::vector<char> hitsAndMisses;

        RandomEngine randomEngine = RandomEngine();

    public:
        battleshipGame();
        ~battleshipGame();
        
        void placeAllShips();
        
        bool isShipHit(Coordinate targetCoord);
        std::vector<bool> const getGameboard() {return gameboard;}
        std::vector<bool> const getRestrictedFields() {return restrictedFields;}
        std::vector<char> const getHitsAndMisses() {return hitsAndMisses;}
    
    private:
        bool const isOccupied(int index);
        bool const isRestricted(int index);

        bool const validateFieldsRightwards(int startingIndex, int shipLen);
        bool const validateFieldsDownwards(int startingIndex, int shipLen);

        std::vector<int> placeShip(int const shipLen);
        std::vector<int> placeShipRightwards(int const shipLen);
        std::vector<int> placeShipDownwards(int const shipLen);
        std::vector<int> setOccupationRightwards(int start, int len);
        std::vector<int> setOccupationDownwards(int start, int len);

        void setRestrictedRightwards(int start, int len);
        void setRestrictedDownwards(int start, int len);
        void updateHitsAndMisses(int index, bool isHit);

        Direction getDirection();

        int convertToGameboardIndex(Coordinate coord);
        int getRealIndexWhenPlacingRightwards(int index, int shipLen);
};