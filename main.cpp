#include "Game.h"

int main(int argc, char** argv)
{
    Game* game = new Game();
    game->Start();
    delete game;
    
    return 0;
}
