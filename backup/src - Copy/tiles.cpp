#include <Vector>
#include <SFML/Graphics.hpp>
#include <vars.hpp>
#include <tiles.hpp>
#include <iostream>

tile::tile(int x, int y, int tileType, std::vector<int> allowedNeighbors)
    : x(x * tileSize), y(y * tileSize), tileType(tileType), allowedNeighbors(allowedNeighbors)
{
    size = tileSize;
    //sprite.setPosition(x, y);

    switch (tileType)
    {
        case tnGrass:
            sprite.setTexture(grassImg);
            break;
        case tnTallGrass:
            sprite.setTexture(tallGrassImg);
            break;
        case tnForest:
            sprite.setTexture(forestImg);
            break;
        case tnSand:
            sprite.setTexture(sandImg);
            break;
        case tnWater:
            sprite.setTexture(waterImg);
            break;
    }
    
    sprite.setColor(sf::Color(255, 255, 255, 255));
}
