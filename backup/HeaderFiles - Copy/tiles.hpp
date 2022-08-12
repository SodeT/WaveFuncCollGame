#ifndef ZODE_TILES_HPP
#define ZODE_TILES_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class tile
{
    public:
    float size;
    float x, y;
    int tileType;
    std::vector<int> allowedNeighbors;

    tile(int x, int y, int tileType, std::vector<int> allowedNeighbors);
    
    sf::Sprite sprite;
};

#endif