#include "player.hpp"
#include <math.h>
#include <iostream>
#include <Thor/Animations.hpp>

Player::Player()
    : m_playerSpeed(100.f)
    , m_texture()
    , a_walking()
    , a_standing()
    , m_animator()
    , m_frameClock()
{
    m_texture.loadFromFile("assets/walking.png");

    this->setTexture(m_texture);
    this->setOrigin(40.f, 25.5f);
    this->setPosition(400, 300);
    this->setScale(0.5f, 0.5f);

    a_walking.addFrame(1.f, sf::IntRect(0,   0, 80, 51)); // 1
    a_walking.addFrame(1.f, sf::IntRect(80,  0, 80, 51)); // 2
    a_walking.addFrame(1.f, sf::IntRect(160, 0, 80, 51)); // 3
    a_walking.addFrame(1.f, sf::IntRect(80,  0, 80, 51)); // 2
    a_walking.addFrame(1.f, sf::IntRect(240, 0, 80, 51)); // 4
    a_walking.addFrame(1.f, sf::IntRect(320, 0, 80, 51)); // 5
    a_walking.addFrame(1.f, sf::IntRect(400, 0, 80, 51)); // 6
    a_walking.addFrame(1.f, sf::IntRect(320, 0, 80, 51)); // 5
    m_animator.addAnimation("walking", a_walking, sf::seconds(1.f));

    a_standing.addFrame(1.f, sf::IntRect(0,0,80,51));
    m_animator.addAnimation("standing", a_standing, sf::seconds(1.f));

    m_animator.playAnimation("standing");
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

    if(m_movingUp || m_movingDown || m_movingLeft || m_movingRight)
    {
        rotate(movement);
        this->move(movement * dT.asSeconds());
        if(!m_walking)
            m_animator.playAnimation("walking", true);
        m_walking = true;
    }
    else
    {
        if(m_walking)
            m_animator.playAnimation("standing");
        m_walking = false;
    }

    m_animator.update(dT);
    m_animator.animate(*this);
}

void Player::rotate(sf::Vector2f destination)
{
        float angle = std::atan2(destination.y, destination.x);
        this->setRotation((angle * 180/3.142) + 90);
}
