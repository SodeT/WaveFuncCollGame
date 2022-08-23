
int gameState;

// terrain generation
int tileSize = 32;
int generationDistance = 50;

std::vector<tile> tiles;
std::vector<std::vector<int>> filledTiles;
std::vector<std::vector<int>> emptyTiles;

// loadingscreens
sf::Texture loadingScreenTexture;
sf::Sprite loadingScreenSprite;

// tiles
sf::Texture grassImg; 
sf::Texture tallGrassImg;
sf::Texture forestImg;
sf::Texture sandImg;
sf::Texture waterImg;

// tile presets
/*
tile grassTile(0, 0, tnGrass, std::vector<int> {tnGrass, tnTallGrass, tnSand});
tile tallGrassTile(0, 0, tnTallGrass, std::vector<int> {tnGrass, tnTallGrass, tnForest});
tile forestTile(0, 0, tnForest, std::vector<int> {tnTallGrass, tnForest});
tile sandTile(0, 0, tnSand, std::vector<int> {tnGrass, tnSand, tnWater});
tile waterTile(0, 0, tnWater, std::vector<int> {tnSand, tnWater});
*/