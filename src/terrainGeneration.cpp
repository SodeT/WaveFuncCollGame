#include <Vector>
#include <Algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <memory>

#include <tiles.hpp>
#include <terraingeneration.hpp>
#include <vars.hpp>

#include <iterator>

//temp
#include <sstream>
#include <string>
#include <iostream>


void findEmptyTiles(float playerX, float playerY)
{
    int playerGridX = playerX / tileSize;
    int playerGridY = playerY / tileSize;

    int generationStartX = playerGridX - generationDistance / 2;
    int generationStartY = playerGridY - generationDistance / 2;

    for (int x = generationStartX; x < generationStartX + generationDistance; x++)
    {
        for (int y = generationStartY; y < generationStartY + generationDistance; y++)
        {
            {
                std::vector<int> key = {x,y};
                if (std::find(filledTiles.begin(), filledTiles.end(), key) == filledTiles.end())
                {
                    emptyTiles.emplace_back(key);
                    
                }
            }
        }
    }
}

void generateTiles()
{

    if (emptyTiles.size() == 0) // if there are no empty tiles to fill
    {
        return;
    }

    tile grassTile(0, 0, tnGrass, {tnGrass, tnTallGrass, tnSand});
    tile tallGrassTile(0, 0, tnTallGrass, {tnGrass, tnTallGrass, tnForest});
    tile forestTile(0, 0, tnForest, {tnTallGrass, tnForest});
    tile sandTile(0, 0, tnSand, {tnGrass, tnSand, tnWater});
    tile waterTile(0, 0, tnWater, {tnSand, tnWater});

    std::vector<int> allowedTilesAmounts;               // the number of allowed tiles           { 3,                                2,                  2                       }
    std::vector<std::vector<int>> tileOptionsList;      // the allowed tiles for that tile index { {tnGrass, tnTallGrass, tnSand},   {tnWater, tnSand},  {tnTallGrass, tnForest} }
    std::vector<std::vector<int>> keys;                 // the positions of the tiles            { {3,6},                            {6,1},              {2,9}                   }

    std::vector<std::vector<int>> tilesAndKeys;         // tile number {{tnGrass, tnTallGrass}, {x, y}}
    std::vector<int> allowedTiles;                      // temp for individual index {tnGrass, tntallGrass}
    std::vector<int> tempKey;                           // temp coordinates {x, y}
    tempKey.reserve(2); // preallocate 2 ints

    for (int i = 0; i < (int)emptyTiles.size(); i++)
    {
        tilesAndKeys = getTileOptions(emptyTiles[i]);

        allowedTilesAmounts.emplace_back(tilesAndKeys[0].size());
        tileOptionsList.push_back(tilesAndKeys[0]);
        keys.push_back(tilesAndKeys[1]);
    }

    //int loopLength = tileOptionsList.size();
    //for (int i = 0; i > loopLength; i++)
    while ((int)tileOptionsList.size() > 0)
    {
        //printf("i: %i", i);
        std::vector<int>::iterator it = std::min_element(allowedTilesAmounts.begin(), allowedTilesAmounts.end()); // gets the tile with the lowest possible amount of neighbors
        int minTileIndex = std::distance(allowedTilesAmounts.begin(), it);

        std::unique_ptr<tile> t;

        int randomTile = tileOptionsList[minTileIndex][rand() % tileOptionsList[minTileIndex].size()];
        switch (randomTile)
        {
            case tnGrass:
                t = std::make_unique<tile>(grassTile);
                break;
            case tnTallGrass:
                t = std::make_unique<tile>(tallGrassTile);
                break;
            case tnForest:
                t = std::make_unique<tile>(forestTile);
                break;
            case tnSand:
                t = std::make_unique<tile>(sandTile);
                break;
            case tnWater:
                t = std::make_unique<tile>(waterTile);
                break;
            default:
                t = std::make_unique<tile>(grassTile);
                break;
        }

        t->x = keys[minTileIndex][0]; 
        t->y = keys[minTileIndex][1];
        t->sprite.setPosition(t->x * tileSize, t->y * tileSize);

        tiles.push_back(*t);
        filledTiles.emplace_back(emptyTiles[minTileIndex]);

        
        allowedTilesAmounts.erase(std::next(allowedTilesAmounts.begin(), minTileIndex));
        tileOptionsList.erase(std::next(tileOptionsList.begin(), minTileIndex));
        keys.erase(std::next(keys.begin(), minTileIndex));

        // Update surrounding tiles
        std::vector<std::vector<int>>::iterator currentTileIt;
        int currentTileIndex;

        // ---------------------------------- +X -----------------------------------------
        tempKey = {keys[minTileIndex][0] + 1, keys[minTileIndex][1]};
        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            currentTileIndex = std::distance(keys.begin(), currentTileIt);
            allowedTiles = getTileOptions(emptyTiles[currentTileIndex])[0];

            allowedTilesAmounts[currentTileIndex] = allowedTiles.size();
            tileOptionsList[currentTileIndex] = allowedTiles;
        }
        
        // ---------------------------------- -X -----------------------------------------
        tempKey = {keys[minTileIndex][0] - 1, keys[minTileIndex][1]};
        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            currentTileIndex = std::distance(keys.begin(), currentTileIt);
            allowedTiles = getTileOptions(emptyTiles[currentTileIndex])[0];

            allowedTilesAmounts[currentTileIndex] = allowedTiles.size();
            tileOptionsList[currentTileIndex] = allowedTiles;
        }

        // ---------------------------------- +Y -----------------------------------------
        tempKey = {keys[minTileIndex][0], keys[minTileIndex][1] + 1};
        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            currentTileIndex = std::distance(keys.begin(), currentTileIt);
            allowedTiles = getTileOptions(emptyTiles[currentTileIndex])[0];

            allowedTilesAmounts[currentTileIndex] = allowedTiles.size();
            tileOptionsList[currentTileIndex] = allowedTiles;
        }

        // ---------------------------------- -Y -----------------------------------------
        tempKey = {keys[minTileIndex][0], keys[minTileIndex][1] - 1};
        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            currentTileIndex = std::distance(keys.begin(), currentTileIt);
            allowedTiles = getTileOptions(emptyTiles[currentTileIndex])[0];

            allowedTilesAmounts[currentTileIndex] = allowedTiles.size();
            tileOptionsList[currentTileIndex] = allowedTiles;

        }
        /*
        printf("_____------____\n");
        for (int h = 0; h < (int)tileOptionsList.size(); h++)
        {
            for (int g = 0; g < (int)tileOptionsList[h].size(); g++)
            {
                printf("%i, ", tileOptionsList[h][g]);
            }
            printf("\n");
        }*/

    }
    return;
}

std::vector<int> checkTileCompatability(std::vector<int> &vec1, std::vector<int> &vec2)
{
    std::vector<int> returnVec;
    std::vector<int>::iterator it; 
    int vecSize;

    if (vec1.size() < vec2.size())
    {
        vecSize = vec2.size();
        for (int i = 0; i < vecSize; i++)
        {
            it = std::find(vec1.begin(), vec1.end(), vec2[i]);
            if (it != vec1.end())
            {
                returnVec.push_back(vec2[i]);
            }
        }
    }
    else
    {
        vecSize = vec1.size();
        for (int i = 0; i < vecSize; i++)
        {
            it = std::find(vec2.begin(), vec2.end(), vec1[i]);
            if (it != vec2.end())
            {
                returnVec.push_back(vec1[i]);
            }
        }
    }
    
    return returnVec;
}

std::vector<std::vector<int>> getTileOptions(std::vector<int> key)
{
    std::vector<int> allowedTiles = {tnGrass, tnTallGrass, tnForest, tnSand, tnWater};
    if (filledTiles.size() == 0)
    {
        return {{tnGrass, tnTallGrass, tnForest, tnSand, tnWater}, key};
    }

    // ==================================== +X                                   filledTiles.begin() - it]
    std::vector<int> tempKey = {key[0] + 1, key[1]};
    std::vector<std::vector<int>>::iterator it; 

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    int tileIndex = std::distance(filledTiles.begin(), it) - 1;

    if (it == filledTiles.end())
    {
        allowedTiles = checkTileCompatability(allowedTiles, tiles[tileIndex].allowedNeighbors);
    }

    // ================================================ -X
    tempKey[0] = key[0] - 1; 
    tempKey[1] = key[1];

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        allowedTiles = checkTileCompatability(allowedTiles, tiles[tileIndex].allowedNeighbors);
    }


    // ======================================= +Y
    tempKey[0] = key[0];
    tempKey[1] = key[1] + 1;

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        allowedTiles = checkTileCompatability(allowedTiles, tiles[tileIndex].allowedNeighbors);
    }


    // =================================== -Y
    tempKey[0] = key[0];
    tempKey[1] = key[1] - 1;

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        allowedTiles = checkTileCompatability(allowedTiles, tiles[tileIndex].allowedNeighbors);
    }

    return {allowedTiles, tempKey};
}
