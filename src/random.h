#include <random>

class RandomEngine 
{ 
public:
    RandomEngine();
    int const getRandomInt(int const min, int const max);
private:
    void initialiseSeed();
};