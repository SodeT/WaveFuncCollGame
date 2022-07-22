#include <vector>
#include <SFML/Graphics.hpp>

class tile
{
    public:
    float x, y, size;
    std::vector<int> allowedNeighbors;
    
    protected:
    sf::Sprite sprite;
};