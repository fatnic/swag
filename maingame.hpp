#pragma once

#include "gamestate.hpp"
#include "player.hpp"
#include <tmx/MapLoader.h>

class MainGame : public GameState
{
public:
    MainGame(Game* game);
    virtual void handleInput();
    virtual void update(sf::Time dT);
    virtual void draw();
private:
    tmx::MapLoader m_mapLoader;
    Player m_player;
    sf::Texture m_texture;
};
