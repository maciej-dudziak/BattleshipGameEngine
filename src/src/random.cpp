#include "../random.h"
#include <time.h>
#include <stdlib.h>

thread_local std::mt19937 gen(std::random_device{} ());

RandomEngine::RandomEngine()
{
    initialiseSeed();
}

int const RandomEngine::getRandomInt(int const min, int const max)
{
    return std::uniform_int_distribution{min, max} (gen);
}

void RandomEngine::initialiseSeed()
{
    srand(time(NULL));
    gen.seed(rand());
}