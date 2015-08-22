#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
    , m_player()
{
    this->game = game;
    loadMap("test-map");

    Guard* guard1 = new Guard(1);
    guard1->setPosition(50,50);

    Guard* guard2 = new Guard(2);
    guard2->setPosition(700,50);

    Guard* guard3 = new Guard(3);
    guard3->setPosition(400,500);

    m_guards.push_back(guard1);
    m_guards.push_back(guard2);
    m_guards.push_back(guard3);

    for(tmx::MapLayer layer: m_mapLoader.GetLayers())
    {
        if(layer.name == "walls")
        {
           addWalls(layer.objects);
        }
        else if(layer.name == "paths")
        {
            for(tmx::MapObject path: layer.objects)
            {
                int guard_id = std::stoi(path.GetName());

                for(Guard* guard: m_guards)
                {
                    if(guard->id == guard_id)
                    {
                        sf::Vector2f origin(path.GetPosition());
                        for(sf::Vector2f point: path.PolyPoints())
                        {
                            sf::Vector2f patrolPoint(origin.x + point.x, origin.y + point.y);
                            guard->addPatrolPoint(patrolPoint);
                        }
                    }
                }
            }
        }
    }

    for(Guard* guard: m_guards)
        guard->initialize();

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
