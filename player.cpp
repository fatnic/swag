#include "player.hpp"
#include <math.h>
#include <iostream>
#include <Thor/Animations.hpp>

Player::Player()
    : _speed(270.f)
    , a_walking()
    , a_standing()
    , _animator()
    , _frameClock()
{
    this->load("assets/player.png");
    this->setOrigin(33.f, 25.5f);
    this->setScale(0.6f, 0.6f);

    a_walking.addFrame(1.f, sf::IntRect(0,   0, 66, 51)); // 1
    a_walking.addFrame(1.f, sf::IntRect(66,  0, 66, 51)); // 2
    a_walking.addFrame(1.f, sf::IntRect(132, 0, 66, 51)); // 3
    a_walking.addFrame(1.f, sf::IntRect(66,  0, 66, 51)); // 2
    a_walking.addFrame(1.f, sf::IntRect(198, 0, 66, 51)); // 4
    a_walking.addFrame(1.f, sf::IntRect(264, 0, 66, 51)); // 5
    a_walking.addFrame(1.f, sf::IntRect(330, 0, 66, 51)); // 6
    a_walking.addFrame(1.f, sf::IntRect(264, 0, 66, 51)); // 5
    _animator.addAnimation("walking", a_walking, sf::seconds(1.f));

    a_standing.addFrame(1.f, sf::IntRect(0,0,66,51));
    _animator.addAnimation("standing", a_standing, sf::seconds(1.f));

    _animator.playAnimation("standing");
}

void Player::handleInput()
{
    _movingUp    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    _movingDown  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    _movingLeft  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    _movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::update(sf::Time dT, std::vector<Wall> walls)
{
    sf::Vector2f prevPos(this->getPosition());
    sf::Vector2f movement(0.f, 0.f);

    if(_movingUp)
        movement.y -= _speed;
    if(_movingDown)
        movement.y += _speed;
    if(_movingLeft)
        movement.x -= _speed;
    if(_movingRight)
        movement.x += _speed;

    if(_movingUp || _movingDown || _movingLeft || _movingRight)
    {
        rotate(movement);
        this->move(movement * dT.asSeconds());

        for(Wall wall: walls)
        {
            if(this->getGlobalBounds().intersects(wall.getGlobalBounds()))
                this->setPosition(prevPos);
        }

        if(!_walking)
            _animator.playAnimation("walking", true);
        _walking = true;
    }
    else
    {
        if(_walking)
            _animator.playAnimation("standing");
        _walking = false;
    }

    _animator.update(dT);
    _animator.animate(*this);
}

void Player::rotate(sf::Vector2f destination)
{
        float angle = std::atan2(destination.y, destination.x);
        this->setRotation((angle * 180/3.142) + 90);
}
