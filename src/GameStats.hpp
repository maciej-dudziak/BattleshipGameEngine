#include <string>

class GameStats
{
private:
    int turnsPlayed;
    int hits;
    int misses;
public:
    GameStats();
    ~GameStats();
    void addPlayedTurn();
    void addHit();
    void addMiss();
    
    int const getTurnsPlayed() { return turnsPlayed; }
    int const getNoOfHits() { return hits; }
    int const getNoOfMisses() { return misses; }
    GameStats& operator+=(const GameStats& rhs);

    std::string to_string();
};

