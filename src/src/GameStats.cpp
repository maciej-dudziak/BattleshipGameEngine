#include "../GameStats.hpp"

GameStats::GameStats() : turnsPlayed(0), hits(0), misses(0)
{
}

GameStats::~GameStats()
{
}

void GameStats::addPlayedTurn()
{
    turnsPlayed++;
}

void GameStats::addHit()
{
    hits++;
}

void GameStats::addMiss()
{
    misses++;
}

GameStats& GameStats::operator+=(const GameStats& rhs)
{
    this->turnsPlayed += rhs.turnsPlayed;
    this->hits += rhs.hits;
    this->misses += rhs.misses;
    return *this;
}

std::string GameStats::to_string()
{
    std::string output;
    output.append(">>> Turns played:    ").append(std::to_string(turnsPlayed)).append("\n");
    output.append(">>> Total hits:      ").append(std::to_string(hits)).append("\n");
    output.append(">>> Total misses     ").append(std::to_string(misses)).append("\n");
    return output;
}