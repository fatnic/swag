#include "guard.hpp"

Guard::Guard()
    : m_walking(false)
{
    this->load("assets/guard.png");

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
    m_animator.addAnimation("walking", a_walking, sf::seconds(1.f));

    a_standing.addFrame(1.f, sf::IntRect(0,0,66,51));
    m_animator.addAnimation("standing", a_standing, sf::seconds(1.f));

    m_animator.playAnimation("standing");
}

void Guard::update(sf::Time dT, std::vector<Wall> walls)
{
    m_animator.update(dT);
    m_animator.animate(*this);
}

