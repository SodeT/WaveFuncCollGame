#ifndef ZODE_VARS_HPP
#define ZODE_VARS_HPP

#include <SFML/Graphics.hpp>


enum gameStates {gsMenu = 0, gsLoading, gsPlaying, gsPaused};
extern int gameState;

enum tileNames {tnGrass = 0, tnTallGrass, tnForest, tnWater}; // TileName grass ==> tnGrass

extern sf::Texture grassImg; 
extern sf::Texture tallGrassImg;
extern sf::Texture forestImg;
extern sf::Texture waterImg;

#endif