#pragma once

#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include "wall.hpp"

class Player : public Entity
{
public:
    Player();
    void handleInput();
    void update(sf::Time dT, std::vector<Wall> walls);
private:
    void rotate(sf::Vector2f destination);
    float _speed;
    bool _movingUp;
    bool _movingDown;
    bool _movingLeft;
    bool _movingRight;
    bool _walking;

    sf::Texture _texture;
    thor::FrameAnimation a_walking;
    thor::FrameAnimation a_standing;
    thor::Animator<Player, std::string> _animator;
    sf::Clock _frameClock;
};
