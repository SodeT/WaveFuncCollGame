// General includes
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory>

// SFML includes
#include <SFML/Graphics.hpp>

// My own includes
#include <vars.hpp>
#include <player.hpp>
#include <tiles.hpp>
#include <loadAssets.hpp>
#include <terraingeneration.hpp>

float screenWidth = 800;
float screenHeight = 600;

time_t ntime;

sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Test");
sf::Clock deltaClock;
sf::Time deltaTime;

#include "assetLoading.cpp"

int main()
{

/*
    loadingScreenTexture.loadFromFile("../assets/art/loading.png");
    loadingScreenSprite.setTexture(loadingScreenTexture);
    loadingScreenSprite.setPosition(0,0);

    // load assets
    gameState = gsLoading;
    window.draw(loadingScreenSprite);
    window.display();
*/
    printf("load\n");
    loadGraphics();
    printf("find empty\n");
    findEmptyTiles(4 * tileSize, 4 * tileSize);
    printf("generate\n");
    generateTiles();
    printf("render\n");
 
    window.clear(sf::Color(23,52,123));
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        std::cout << tiles[i].x << ", " << tiles[i].y << std::endl;
        window.draw(tiles[i].sprite);
    }

    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
    }
    return 0;
}
