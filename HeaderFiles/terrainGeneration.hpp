#ifndef ZODE_TERRAINGENERATION_HPP
#define ZODE_TERRAINGENERATION_HPP

#include <tiles.hpp>


void findEmptyTiles(float playerX, float playerY);
void generateTiles();
std::vector<int> checkTileCompatability(std::vector<int> &vec1, std::vector<int> &vec2);
std::vector<std::vector<int>> getTileOptions(std::vector<int> key);

#endif