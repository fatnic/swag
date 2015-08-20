#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
{
    this->game = game;
}

void MainGame::draw()
{
    return;
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
}

void MainGame::update(sf::Time dT)
{

}
