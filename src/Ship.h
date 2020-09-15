#include <vector>

class Ship
{
private:
    std::vector<int> occupiedFields;
public:
    Ship(std::vector<int> _occupiedFields);
    int const getNumberOfOccupiedFields();
    
};

Ship::Ship(std::vector<int> _occupiedFields) : occupiedFields(_occupiedFields)
{
}

int const Ship::getNumberOfOccupiedFields()
{
    return occupiedFields.size();
}