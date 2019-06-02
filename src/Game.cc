#include "Game.hh"

Game::Game()
{
}

Game::~Game()
{
}

void Game::runStepByStep()
{
    Snake snake(direction::right, Point2D(5,5));
    Map map(20,20);
    direction input;
    while(snake.isAlive())
    {
        std::vector<Point2D> allPoints = snake.getAllPoints();
        map.update(allPoints);
        map.print();
        input = getInput();
        snake.turn(input);
        snake.move(map);
    }
    std::cout << "GAME OVER" << std::endl;
}

void Game::runContinuous()
{
}
