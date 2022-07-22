#include <vars.hpp>
#include "tile.cpp"

class grassTile : public tile
{
    grasstile()
    {
        allowedNeighbors = (std::vector<int>){tnGrass, tnTallGrass};
        sprite.setTexture(grassMat);
    }
};

class tallGrassTile: public tile
{
    tallGrasstile()
    {
        allowedNeighbors = (std::vector<int>){tnGrass, tnTallGrass, tnForest};
        sprite.setTexture(tallGrassMat);
    }
};

class forestTile: public tile
{
    forestTile()
    {
        allowedNeighbors = (std::vector<int>){tnTallGrass, tnForest, tnWater};
        sprite.setTexture(forestMat);
    }
};

class waterTile: public tile
{
    watertile()
    {
        allowedNeighbors = (std::vector<int>){tnForest, tnWater};
        sprite.setTexture(waterMat);
    }
};