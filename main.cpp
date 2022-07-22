// General includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

// My own includes
#include <vars.hpp>
#include <player.hpp>
#include <tileMap.hpp>
#include <loadAssets.hpp>

sf::RenderWindow window(sf::VideoMode(700, 400), "Test");

int main()
{
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