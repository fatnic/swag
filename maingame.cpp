#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : m_mapLoader("assets/")
    , m_texture()
    , m_player()
{
    this->game = game;
    m_texture.loadFromFile("assets/player1.png");
    m_player.setTexture(m_texture);
    m_player.setOrigin(m_player.getGlobalBounds().width / 2, m_player.getGlobalBounds().height / 2);
    m_player.setPosition(game->window.getSize().x/2, game->window.getSize().y/2);
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
