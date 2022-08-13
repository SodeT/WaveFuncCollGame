#ifndef ZODE_TERRAINGENERATION_HPP
#define ZODE_TERRAINGENERATION_HPP

#include <tiles.hpp>

void findEmptyTiles(float playerX, float playerY);
void generateTiles();
void checkTileCompatability(std::vector<int>* returnVec);
std::vector<std::vector<int>> getTileOptions(std::vector<int> key);

#endif