#include "wall.hpp"
#include <iostream>

Wall::Wall(sf::FloatRect wall)
{
    this->setPosition(wall.left, wall.top);
    this->setSize(sf::Vector2f(wall.width, wall.height));
    this->setFillColor(sf::Color::Green);

    std::cout << "Wall: " << this->getSize().x << ":" << this->getSize().y << std::endl;
}

