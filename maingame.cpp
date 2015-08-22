#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
    , m_player()
{
    this->game = game;
    loadMap("test-map");

    for(tmx::MapLayer layer: m_mapLoader.GetLayers())
    {
        if(layer.name == "walls")
            addWalls(layer.objects);
        else if(layer.name == "guards")
            addGuards(layer.objects);
    }

    m_player.setPosition(400, 300);
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
    for(Guard* guard: m_guards)
        guard->update(dT, m_walls);
}

void MainGame::draw()
{
    game->window.draw(m_mapLoader);
    //    for(Wall wall: m_walls)
    //        game->window.draw(wall);
    for(Guard* guard: m_guards)
        game->window.draw(*guard);

    game->window.draw(m_player);
    return;
}

void MainGame::loadMap(std::string tmxfilename)
{
    m_mapLoader.Load(tmxfilename + ".tmx");
}

void MainGame::addWalls(tmx::MapObjects walls)
{

    for(tmx::MapObject wall: walls)
    {
        Wall nwall(wall.GetAABB());
        m_walls.push_back(nwall);
    }
}

void MainGame::addGuards(tmx::MapObjects guards)
{
    for(tmx::MapObject path: guards)
    {
        int guard_id = std::stoi(path.GetName());
        Guard* guard = new Guard(guard_id);
        guard->addPatrolPoints(path);
        m_guards.push_back(guard);
    }
}
