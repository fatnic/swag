#pragma once
#include "entity.hpp"
#include <Thor/Animations.hpp>
#include "wall.hpp"

class Guard : public Entity
{
public:
    Guard();
    void update(sf::Time dT, std::vector<Wall> walls);
private:
    bool m_walking;
    thor::FrameAnimation a_walking;
    thor::FrameAnimation a_standing;
    thor::Animator<Guard, std::string> m_animator;
    sf::Clock m_frameClock;
};
