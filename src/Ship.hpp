#include <vector>
#include <algorithm>

class Ship
{
private:
    std::vector<int> occupiedFields;
public:
    Ship(std::vector<int> _occupiedFields);
    bool const removeIfFound(int index);
    int const getNumberOfOccupiedFields();
};