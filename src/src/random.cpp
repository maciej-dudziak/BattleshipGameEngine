#include "../random.hpp"
#include <chrono>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
thread_local std::mt19937 gen(seed);

RandomEngine::RandomEngine()
{
}

int const RandomEngine::getRandomInt(int const min, int const max)
{
    return std::uniform_int_distribution{min, max} (gen);
}