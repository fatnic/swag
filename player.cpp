#include "player.hpp"
#include <math.h>

Player::Player()
    : m_playerSpeed(200.f)
{
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W)
        m_movingUp = isPressed;
    if(key == sf::Keyboard::S)
        m_movingDown = isPressed;
    if(key == sf::Keyboard::A)
        m_movingLeft = isPressed;
    if(key == sf::Keyboard::D)
        m_movingRight = isPressed;
}

void Player::update(sf::Time dT)
{
    sf::Vector2f movement(0.f, 0.f);
    if(m_movingUp)
        movement.y -= m_playerSpeed;
    if(m_movingDown)
        movement.y += m_playerSpeed;
    if(m_movingLeft)
        movement.x -= m_playerSpeed;
    if(m_movingRight)
        movement.x += m_playerSpeed;

    rotate(movement);
    this->move(movement * dT.asSeconds());
}

void Player::rotate(sf::Vector2f destination)
{
    if(m_movingUp || m_movingDown || m_movingLeft || m_movingRight)
    {
        float angle = std::atan2(destination.y, destination.x);
        this->setRotation((angle * 180/3.142) + 90);
    }
}

