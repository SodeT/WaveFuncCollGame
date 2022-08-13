#include <Vector>
#include <Algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <memory>

#include <tiles.hpp>
#include <terraingeneration.hpp>
#include <vars.hpp>

//temp
#include <sstream>
#include <string>
#include <iostream>

int allocatedBytes = 0;

void* operator new(size_t size)
{
    allocatedBytes += size;
    return malloc(size);
}

void operator delete(void* mem, size_t size)
{
    allocatedBytes -= size;
    free(mem);
}


void findEmptyTiles(float playerX, float playerY)
{
    std::cout << "find begining bytes: " << allocatedBytes << std::endl;
    int playerGridX = playerX / tileSize;
    int playerGridY = playerY / tileSize;

    int generationStartX = playerGridX - generationDistance / 2;
    int generationStartY = playerGridY - generationDistance / 2;

    for (int x = generationStartX; x < generationStartX + generationDistance; x++)
    {
        for (int y = generationStartY; y < generationStartY + generationDistance; y++)
        {
            std::vector<int> key = {x,y};
            if (std::find(filledTiles.begin(), filledTiles.end(), key) == filledTiles.end())
            {
                emptyTiles.emplace_back(key);
            }
        }
    }
    std::cout << "find end bytes: " << allocatedBytes << std::endl;
}

void generateTiles()
{
    std::cout << "begining bytes: " << allocatedBytes << std::endl;

    tile grassTile(0, 0, tnGrass, {tnGrass, tnTallGrass, tnSand});
    tile tallGrassTile(0, 0, tnTallGrass, {tnGrass, tnTallGrass, tnForest});
    tile forestTile(0, 0, tnForest, {tnTallGrass, tnForest});
    tile sandTile(0, 0, tnSand, {tnGrass, tnSand, tnWater});
    tile waterTile(0, 0, tnWater, {tnSand, tnWater});

    std::vector<int> allowedTilesAmounts;
    std::vector<std::vector<int>> tileOptionsList;
    std::vector<std::vector<int>> keys;

    std::vector<std::vector<int>> tilesAndKeys;
    std::vector<int> allowedTiles;
    std::vector<int> tempKey;

    for (int i = 0; i < (int)emptyTiles.size(); i++)
    {
        tilesAndKeys = getTileOptions(emptyTiles[i]);

        allowedTiles = tilesAndKeys[0];
        tempKey = tilesAndKeys[1];

        allowedTilesAmounts.emplace_back(allowedTiles.size());
        tileOptionsList.emplace_back(allowedTiles);
        keys.emplace_back(tempKey);
    }

    int loopLength = tileOptionsList.size();
    for (int i = 0; i < loopLength; i++)
    {
        std::vector<int>::iterator it = std::min_element(allowedTilesAmounts.begin(), allowedTilesAmounts.end()); // gets the tile with the lowest possible amount of neighbors
        int minTileIndex = std::distance(allowedTilesAmounts.begin(), it);

        std::unique_ptr<tile> t;

        int randomTile = tileOptionsList[i][rand() % tileOptionsList[i].size()];
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
        }

        t->x = keys[minTileIndex + i][0]; 
        t->y = keys[minTileIndex + i][1]; 
        t->sprite.setPosition(t->x * tileSize, t->y * tileSize);

        tiles.emplace_back(*t);
        filledTiles.emplace_back(emptyTiles[minTileIndex]);

        // Update surrounding tiles
        tempKey = {keys[minTileIndex + i][0] + 1, keys[minTileIndex + i][1]};
        std::vector<std::vector<int>>::iterator currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        printf("+X?\n");
        if (currentTileIt != keys.end())
        {
            int currentTile = std::distance(keys.begin(), currentTileIt);

            allowedTiles = getTileOptions(emptyTiles[currentTile])[0];

            allowedTilesAmounts[i] = allowedTiles.size();
            tileOptionsList[i] = allowedTiles;
        }
        
        tempKey = {keys[minTileIndex + i][0] - 1, keys[minTileIndex + i][1]};

        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            int currentTile = std::distance(keys.begin(), currentTileIt);

            allowedTiles = getTileOptions(emptyTiles[currentTile])[0];

            allowedTilesAmounts[i] = allowedTiles.size();
            tileOptionsList[i] = allowedTiles;
        }

        tempKey = {keys[minTileIndex + i][0], keys[minTileIndex + i][1] + 1};

        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            int currentTile = std::distance(keys.begin(), currentTileIt);

            allowedTiles = getTileOptions(emptyTiles[currentTile])[0];

            allowedTilesAmounts[i] = allowedTiles.size();
            tileOptionsList[i] = allowedTiles;
        }

        tempKey = {keys[minTileIndex + i][0], keys[minTileIndex + i][1] - 1};

        currentTileIt = std::find(keys.begin(), keys.end(), tempKey);
        if (currentTileIt != keys.end())
        {
            int currentTile = std::distance(keys.begin(), currentTileIt);

            allowedTiles = getTileOptions(emptyTiles[currentTile])[0];

            allowedTilesAmounts[i] = allowedTiles.size();
            tileOptionsList[i] = allowedTiles;
        }
    }

    allowedTilesAmounts = {};
    tileOptionsList = {};
    keys = {};
    emptyTiles = {};

    return;

}

void checkTileCompatability(std::vector<int>* returnVec) //std::vector<int> vec1, std::vector<int> vec2, std::vector<int>* returnVec)
{
    printf("inside\n");
    /*
    std::vector<int>::iterator it; 
    if (vec1.size() < vec2.size())
    {
        for (int i = 0; i < (int)vec2.size(); i++)
        {
            it = std::find(vec1.begin(), vec1.end(), vec2[i]);
            if (it != vec1.end())
            {
                returnVec->push_back(vec2[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < (int)vec1.size(); i++)
        {
            it = std::find(vec2.begin(), vec2.end(), vec1[i]);
            if (it != vec2.end())
            {
                returnVec->push_back(vec1[i]);
            }
        }
    }
    */
    printf("return\n");
    return;
}

std::vector<std::vector<int>> getTileOptions(std::vector<int> key)
{
    std::vector<int> allowedTiles = {tnGrass, tnTallGrass, tnForest, tnSand, tnWater};
    if ((int)filledTiles.size() == 0)
    {
        return {{tnGrass}, key};
    }

    // ==================================== +X
    std::vector<int> tempKey = {key[0] + 1, key[1]};
    std::vector<std::vector<int>>::iterator it; 

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        std::cout << "end bytes: " << allocatedBytes << std::endl;
        printf("before\n");
        //checkTileCompatability(&allowedTiles);//tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles, &allowedTiles);
        printf("after\n");
    }

    // ================================================ -X
    tempKey[0] = key[0] - 1; 
    tempKey[1] = key[1];

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        //checkTileCompatability(&allowedTiles);//tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles, &allowedTiles);
    }


    // ======================================= +Y
    tempKey[0] = key[0];
    tempKey[1] = key[1] + 1;

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        //checkTileCompatability(&allowedTiles);//tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles, &allowedTiles);
    }


    // =================================== -Y
    tempKey[0] = key[0];
    tempKey[1] = key[1] - 1;

    it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
    if (it == filledTiles.end())
    {
        //checkTileCompatability(&allowedTiles);//tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles, &allowedTiles);
    }

    return {allowedTiles, tempKey};
}

/*
for (int i = 0; i < (int)emptyTiles.size(); i++)
    {
        int key[2];
        std::memcpy(&key, &emptyTiles[i], sizeof(key));
        std::vector<int> allowedTiles = {0, 1, 2, 3, 4};

        // ==================================== +X
        std::vector<int> tempKey = {key[0] + 1, key[1]};
        std::vector<std::vector<int>>::iterator it; 
        it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
        if (it != filledTiles.end())
        {
            allowedTiles = checkTileCompatability(tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles);
        }

        // ================================================ -X
        tempKey[0] = key[0] - 1; 
        tempKey[1] = key[1];

        it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
        if (it != filledTiles.end())
        {
            allowedTiles = checkTileCompatability(tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles);
        }

        // ======================================= +Y
        tempKey[0] = key[0];
        tempKey[1] = key[1] + 1;

        it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
        if (it != filledTiles.end())
        {
            allowedTiles = checkTileCompatability(tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles);
        }

        // =================================== -Y
        tempKey[0] = key[0];
        tempKey[1] = key[1] - 1;

        it = std::find(filledTiles.begin(), filledTiles.end(), tempKey);
        if (it != filledTiles.end())
        {
            allowedTiles = checkTileCompatability(tiles[it - filledTiles.begin()].allowedNeighbors, allowedTiles);
        }
        
        keys.emplace_back(tempKey);
        tileOptionsList.emplace_back(allowedTiles);
        allowedTilesAmounts.emplace_back(allowedTiles.size());
    }
    */