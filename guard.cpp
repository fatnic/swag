#include "guard.hpp"
#include "math.h"
#include <iostream>

Guard::Guard(int id)
    : _walking(false)
    , id(id)
    , _speed(60.f)
{
    this->load("assets/guard.png");

    this->setOrigin(33.f, 25.5f);
    this->setScale(0.6f, 0.6f);

    // TODO: Put all this into an animation builder class
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

void Guard::update(sf::Time dT, std::vector<Wall> walls)
{
    sf::Vector2f diff(this->getPosition() - _target);

    if(!_atTarget)
    {
        if(!_walking)
        {
            _walking = true;
            _animator.playAnimation("walking", true);
        }

        sf::Vector2f movement(0.f, 0.f);

        float rotation = std::atan2(diff.y, diff.x);
        this->setRotation((rotation * 180/3.124) - 90);

        movement.x = -std::cos(rotation) * _speed;
        movement.y = -std::sin(rotation) * _speed;
        this->move(movement * dT.asSeconds());
    }

    if(abs(diff.x) <= 2 && abs(diff.y) <= 1)
    {
        if(_walking)
        {
            _walking = false;
            _animator.playAnimation("standing");
            _waiting.restart();
            _atTarget = true;
        }

        if(_waiting.getElapsedTime().asSeconds() >= 5)
        {
            setTarget(*_ppIt);
            _ppIt++;

            if(_ppIt == _patrolPoints.end())
                _ppIt = _patrolPoints.begin();

            _atTarget = false;
        }
    }

    _animator.update(dT);
    _animator.animate(*this);
}

void Guard::setTarget(sf::Vector2f target)
{
    _target = target;
}

void Guard::addPatrolPoints(tmx::MapObject points)
{
    sf::Vector2f origin(points.GetPosition());
    for(sf::Vector2f point: points.PolyPoints())
    {
        sf::Vector2f patrolPoint(origin.x + point.x, origin.y + point.y);
        _patrolPoints.push_back(patrolPoint);
    }
    initialize();
    setPosition(_patrolPoints[0]);

}

void Guard::initialize()
{
    if(_patrolPoints.size() == 0)
        _patrolPoints.push_back(sf::Vector2f(this->getPosition().x, this->getPosition().y));

    _ppIt = _patrolPoints.begin();
    setTarget(*_ppIt);
    _ppIt++;

    if(_ppIt == _patrolPoints.end())
        _ppIt = _patrolPoints.begin();

}
