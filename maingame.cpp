#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
    , m_player()
    , m_guard()
{
    this->game = game;
    loadMap("test-map");
    addWalls();

    m_player.setPosition(400, 300);
    m_guard.setPosition(50,50);
}

void MainGame::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            game->window.close();
            break;
        }
    }
    m_player.handleInput();
}

void MainGame::update(sf::Time dT)
{
    m_player.update(dT, m_walls);
    m_guard.update(dT, m_walls);
}

void MainGame::draw()
{
    game->window.draw(m_mapLoader);
//    for(Wall wall: m_walls)
//        game->window.draw(wall);
    game->window.draw(m_guard);
    game->window.draw(m_player);
    return;
}

void MainGame::loadMap(std::string tmxfilename)
{
    m_mapLoader.Load(tmxfilename + ".tmx");
}

void MainGame::addWalls()
{
    for(tmx::MapLayer layer: m_mapLoader.GetLayers())
    {
        if(layer.name == "walls")
        {
          for(tmx::MapObject wall: layer.objects)
          {
              Wall nwall(wall.GetAABB());
              m_walls.push_back(nwall);
          }
        }
    }
}
