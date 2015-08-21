#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
    Entity();
    void load(std::string texturefilename);
    ~Entity();
private:
    sf::Texture m_texture;
};
