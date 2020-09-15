#include "../Ship.h"

Ship::Ship(std::vector<int> _occupiedFields) : occupiedFields(_occupiedFields)
{
}

int const Ship::getNumberOfOccupiedFields()
{
    return occupiedFields.size();
}

bool const Ship::removeIfFound(int index)
{
    auto res = std::find(begin(occupiedFields), end(occupiedFields), index);
    bool isFound = (res != end(occupiedFields));
    if(isFound)
    {
        occupiedFields.erase(res);
    }
    return isFound;
}