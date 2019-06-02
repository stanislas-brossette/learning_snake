#include <iostream>
#include "Game.hh"


int main(void)
{
    Game game;
    //game.runStepByStep();
    game.runContinuous(0.1);

    return 0;
}
