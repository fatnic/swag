#include "guard.hpp"
#include "math.h"
#include <iostream>

Guard::Guard(int id)
    : m_walking(false)
    , id(id)
    , m_speed(60.f)
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
    m_animator.addAnimation("walking", a_walking, sf::seconds(1.f));

    a_standing.addFrame(1.f, sf::IntRect(0,0,66,51));
    m_animator.addAnimation("standing", a_standing, sf::seconds(1.f));

    m_animator.playAnimation("standing");
}

void Guard::update(sf::Time dT, std::vector<Wall> walls)
{
    sf::Vector2f diff(this->getPosition() - m_target);

    if(!m_atTarget)
    {
        if(!m_walking)
        {
            m_walking = true;
            m_animator.playAnimation("walking", true);
        }

        sf::Vector2f movement(0.f, 0.f);

        float rotation = std::atan2(diff.y, diff.x);
        this->setRotation((rotation * 180/3.124) - 90);

        movement.x = -std::cos(rotation) * m_speed;
        movement.y = -std::sin(rotation) * m_speed;
        this->move(movement * dT.asSeconds());
    }

    if(abs(diff.x) <= 2 && abs(diff.y) <= 1)
    {
        if(m_walking)
        {
            m_walking = false;
            m_animator.playAnimation("standing");
            m_waiting.restart();
            m_atTarget = true;
        }

        if(m_waiting.getElapsedTime().asSeconds() >= 5)
        {
            setTarget(*m_ppIt);
            m_ppIt++;

            if(m_ppIt == m_patrolPoints.end())
                m_ppIt = m_patrolPoints.begin();

            m_atTarget = false;
        }
    }

    m_animator.update(dT);
    m_animator.animate(*this);
}

void Guard::setTarget(sf::Vector2f target)
{
    m_target = target;
}

void Guard::addPatrolPoints(tmx::MapObject points)
{
    sf::Vector2f origin(points.GetPosition());
    for(sf::Vector2f point: points.PolyPoints())
    {
        sf::Vector2f patrolPoint(origin.x + point.x, origin.y + point.y);
        m_patrolPoints.push_back(patrolPoint);
    }
    initialize();
    setPosition(m_patrolPoints[0]);

}

void Guard::initialize()
{
    if(m_patrolPoints.size() == 0)
        m_patrolPoints.push_back(sf::Vector2f(this->getPosition().x, this->getPosition().y));

    m_ppIt = m_patrolPoints.begin();
    setTarget(*m_ppIt);
    m_ppIt++;

    if(m_ppIt == m_patrolPoints.end())
        m_ppIt = m_patrolPoints.begin();

}
