#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

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
    bool m_walking;

    sf::Texture m_texture;
    thor::FrameAnimation a_walking;
    thor::FrameAnimation a_standing;
    thor::Animator<Player, std::string> m_animator;
    sf::Clock m_frameClock;
};
