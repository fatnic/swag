#pragma once
#include "entity.hpp"
#include <Thor/Animations.hpp>
#include <tmx/MapObject.h>
#include "wall.hpp"
#include <vector>

class Guard : public Entity
{
public:
    Guard(int id);
    int id;
    void update(sf::Time dT, std::vector<Wall> walls);
    void setTarget(sf::Vector2f target);
    void addPatrolPoints(tmx::MapObject path);
    void initialize();
private:
    float _speed;
    bool _walking;
    thor::FrameAnimation a_walking;
    thor::FrameAnimation a_standing;
    thor::Animator<Guard, std::string> _animator;
    sf::Clock _frameClock;
    sf::Vector2f _target;
    bool _atTarget;
    std::vector<sf::Vector2f> _patrolPoints;
    std::vector<sf::Vector2f>::iterator _ppIt;
    sf::Clock _waiting;
};
