#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : _mapLoader("assets/")
    , _player()
    , _view()
{
    this->game = game;
    loadMap("land");

    for(tmx::MapLayer layer: _mapLoader.GetLayers())
    {
        if(layer.name == "walls")
            addWalls(layer.objects);
        else if(layer.name == "guards")
            addGuards(layer.objects);
        else if(layer.name == "spawns")
            setSpawnPoints(layer.objects);
    }

    _view.setSize(sf::Vector2f(game->window.getSize().x, game->window.getSize().y));
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
    _player.handleInput();
}

void MainGame::update(sf::Time dT)
{
    _player.update(dT, _walls);

    for(Guard* guard: _guards)
        guard->update(dT, _walls);

    calcView();
}

void MainGame::draw()
{
    game->window.draw(_mapLoader);

    for(Guard* guard: _guards)
        game->window.draw(*guard);

    game->window.draw(_player);
    return;
}

void MainGame::loadMap(std::string tmxfilename)
{
    _mapLoader.Load(tmxfilename + ".tmx");
}

void MainGame::addWalls(tmx::MapObjects walls)
{

    for(tmx::MapObject wall: walls)
    {
        Wall nwall(wall.GetAABB());
        _walls.push_back(nwall);
    }
}

void MainGame::addGuards(tmx::MapObjects guards)
{
    for(tmx::MapObject path: guards)
    {
        int guard_id = std::stoi(path.GetName());
        Guard* guard = new Guard(guard_id);
        guard->addPatrolPoints(path);
        _guards.push_back(guard);
    }
}

void MainGame::setSpawnPoints(tmx::MapObjects spawns)
{
    for(tmx::MapObject spawn: spawns)
    {
        if(spawn.GetName() == "player")
            _player.setPosition(spawn.GetPosition());
    }
}

void MainGame::calcView()
{
    sf::Vector2f newView(_player.getPosition());

    if(_player.getPosition().x - game->window.getSize().x / 2 < 0)
        newView.x = 0 + game->window.getSize().x / 2;

    if(_player.getPosition().x + game->window.getSize().x / 2 > _mapLoader.GetMapSize().x)
        newView.x = _mapLoader.GetMapSize().x - game->window.getSize().x / 2;

    if(_player.getPosition().y - game->window.getSize().y / 2 < 0)
        newView.y = 0 + game->window.getSize().y / 2;

    if(_player.getPosition().y + game->window.getSize().y / 2 > _mapLoader.GetMapSize().y)
        newView.y = _mapLoader.GetMapSize().y - game->window.getSize().y / 2;

    _view.setCenter(newView);
    game->window.setView(_view);
}
