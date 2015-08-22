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
    float m_speed;
    bool m_walking;
    thor::FrameAnimation a_walking;
    thor::FrameAnimation a_standing;
    thor::Animator<Guard, std::string> m_animator;
    sf::Clock m_frameClock;
    sf::Vector2f m_target;
    bool m_atTarget;
    std::vector<sf::Vector2f> m_patrolPoints;
    std::vector<sf::Vector2f>::iterator m_ppIt;
    sf::Clock m_waiting;
};
