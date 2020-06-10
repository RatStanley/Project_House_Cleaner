#include "game.h"

int main()
{
    Game *game;
    game = new Game;
    game->Game_loop();
    delete game;
}
