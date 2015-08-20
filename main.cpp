#include "game.hpp"
#include "maingame.hpp"

int main()
{
    Game game(sf::VideoMode(800,600), "GameWindow");
    game.pushState(new MainGame(&game));
    game.gameLoop();
}


