#include <vars.hpp>
#include <SFML/Graphics.hpp>

void loadGraphics()
{
    grassImg.loadFromFile("../assets/art/tiles/grass.png");
    tallGrassImg.loadFromFile("../assets/art/tiles/tallGrass.png");
    forestImg.loadFromFile("../assets/art/tiles/forest.png");
    waterImg.loadFromFile("../assets/art/tiles/water.png");
}