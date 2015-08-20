#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
    , m_player()
{
    this->game = game;
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
    m_player.update(dT);
}

void MainGame::draw()
{
    game->window.draw(m_player);
    return;
}
