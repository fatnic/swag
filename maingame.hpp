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
    tmx::MapLoader _mapLoader;
    sf::View _view;
    Player _player;
    sf::Texture _texture;
    void loadMap(std::string tmxfilename);
    void addWalls(tmx::MapObjects walls);
    void addGuards(tmx::MapObjects guards);
    void setSpawnPoints(tmx::MapObjects spawns);
    void calcView();
    std::vector<Wall> _walls;
    std::vector<Guard*> _guards;
};
