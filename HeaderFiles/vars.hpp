#ifndef ZODE_VARS_HPP
#define ZODE_VARS_HPP

#include <SFML/Graphics.hpp>

extern enum tileNames {tnGrass = 0, tnTallGrass, tnForest, tnWater}; // TileName grass ==> tnGrass
extern sf::Texture grassMat, tallGrassMat, forestMat, waterMat; // Textures in global scope so they are always loaded 

#endif