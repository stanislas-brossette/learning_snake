#include <iostream>
#include "Game.hh"
#include "agents/Agent.hh"


int main(void)
{
    Game game;
    //game.runStepByStep();
    //game.runContinuous();

    Agent* agent = new AStarAgent();
    game.runAgent(agent);
    delete agent;

    return 0;
}
