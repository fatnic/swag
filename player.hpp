#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
public:
    Player();
    void handleInput();
    void update(sf::Time dT);
private:
    void rotate(sf::Vector2f destination);
    float m_playerSpeed;
    bool m_movingUp;
    bool m_movingDown;
    bool m_movingLeft;
    bool m_movingRight;
    sf::Texture m_texture;
};
