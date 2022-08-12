#ifndef ZODE_VARS_HPP
#define ZODE_VARS_HPP

#include <SFML/Graphics.hpp>
#include <tiles.hpp>

enum gameStates {gsMenu = 0, gsLoading, gsPlaying, gsPaused};
extern int gameState;

enum tileNames {tnGrass = 0, tnTallGrass, tnForest, tnSand, tnWater}; // TileName grass ==> tnGrass

extern int tileSize;
extern int generationDistance;

extern std::vector<tile> tiles;
extern std::vector<std::vector<int>> filledTiles;
extern std::vector<std::vector<int>> emptyTiles;

extern sf::Texture grassImg; 
extern sf::Texture tallGrassImg;
extern sf::Texture forestImg;
extern sf::Texture sandImg;
extern sf::Texture waterImg;

// tile presets
/*
extern tile grassTile(0, 0, tnGrass, std::vector<int> {tnGrass, tnTallGrass, tnSand});
extern tile tallGrassTile(0, 0, tnTallGrass, std::vector<int> {tnGrass, tnTallGrass, tnForest});
extern tile forestTile(0, 0, tnForest, std::vector<int> {tnTallGrass, tnForest});
extern tile sandTile(0, 0, tnSand, std::vector<int> {tnGrass, tnSand, tnWater});
extern tile waterTile(0, 0, tnWater, std::vector<int> {tnSand, tnWater});
*/
#endif