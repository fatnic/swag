#pragma once

#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include "wall.hpp"

class Player : public Entity
{
public:
    Player();
    void handleInput();
    void update(sf::Time dT, std::vector<Wall> walls);
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
