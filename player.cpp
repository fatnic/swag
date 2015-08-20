#include "player.hpp"
#include <math.h>
#include <iostream>

Player::Player()
    : m_playerSpeed(100.f)
    , m_texture()
{
    m_texture.loadFromFile("assets/player1.png");

    this->setTexture(m_texture);
    this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
    this->setPosition(400, 300);
    this->setScale(0.5f, 0.5f);
}

void Player::handleInput()
{
    m_movingUp    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    m_movingDown  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    m_movingLeft  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    m_movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
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

