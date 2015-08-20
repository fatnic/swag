#pragma once

#include "gamestate.hpp"
#include <tmx/MapLoader.h>

class MainGame : public GameState
{
public:
    MainGame(Game* game);
    virtual void draw();
    virtual void handleInput();
    virtual void update(sf::Time dT);
private:
    tmx::MapLoader m_mapLoader;
};
