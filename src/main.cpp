// General includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

// My own includes
//#include "assetLoading.cpp"
#include <vars.hpp>
#include <player.hpp>
#include <tileMap.hpp>
#include <loadAssets.hpp>


sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
sf::Clock deltaClock;
sf::Time deltaTime;

int gameState;


// loadingscreens
sf::Texture loadingScreenTexture;
sf::Sprite loadingScreenSprite;

// tiles
sf::Texture grassImg; 
sf::Texture tallGrassImg;
sf::Texture forestImg;
sf::Texture waterImg;

int main()
{
    loadingScreenTexture.loadFromFile("../assets/art/loading.png");
    loadingScreenSprite.setTexture(loadingScreenTexture);
    loadingScreenSprite.setPosition(0,0);

    //gameState = gsLoading;
    window.draw(loadingScreenSprite);

    loadGraphics();
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