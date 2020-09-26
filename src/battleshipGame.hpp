#pragma once
#include <vector>
#include "random.hpp"
#include "Coordinate.hpp"
#include "Ship.hpp"
#include "GameStats.hpp"

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
        std::vector<Ship> ships;

        RandomEngine randomEngine = RandomEngine();
        GameStats gameStats = GameStats();

    public:
        battleshipGame();
        battleshipGame(int _boardsize);
        ~battleshipGame();
        
        void placeAllShips();
        void resizeGame(int newGameboardSize);
        bool isShipHit(Coordinate targetCoord);
        bool const canBeShoot(Coordinate targetCoord);

        int const getShipCount() {return ships.size();}
        std::vector<bool> const getGameboard() {return gameboard;}
        std::vector<char> const getHitsAndMisses() {return hitsAndMisses;}
        GameStats const getGameStats() { return gameStats; }
    
    private:
        bool const isOccupied(int index);
        bool const isRestricted(int index);

        bool const validateFieldsRightwards(int startingIndex, int shipLen);
        bool const validateFieldsDownwards(int startingIndex, int shipLen);
        bool const validateCoord(Coordinate coord);

        std::vector<int> placeShip(int const shipLen);
        std::vector<int> placeShipRightwards(int const shipLen);
        std::vector<int> placeShipDownwards(int const shipLen);
        std::vector<int> setOccupationRightwards(int start, int len);
        std::vector<int> setOccupationDownwards(int start, int len);

        void setRestrictedRightwards(int start, int len);
        void setRestrictedDownwards(int start, int len);
        void updateGameStatus(int index, bool isHit);
        void updateHitsAndMisses(int index, bool isHit);
        void updateShipCount(int index);
        void updateGameStats(bool shootResult);

        Direction getDirection();

        int convertToGameboardIndex(Coordinate coord);
        int getRealIndexWhenPlacingRightwards(int index, int shipLen);
};