#pragma once

#include "gamestate.hpp"
#include "player.hpp"
#include "guard.hpp"
#include <tmx/MapLoader.h>
#include "wall.hpp"
#include <vector>

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
    void loadMap(std::string tmxfilename);
    void addWalls(tmx::MapObjects walls);
    std::vector<Wall> m_walls;
    std::vector<Guard*> m_guards;
};
