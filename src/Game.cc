#include "Game.hh"
#include <thread>
#include <ctime>

Game::Game()
  : snake_(direction::right, Point2D(5,5)),
    map_(40,30,2),
    clock_(),
    frequency_(0.08)
{
}

Game::~Game()
{
}

void Game::runStepByStep()
{
    direction input;
    while(snake_.isAlive())
    {
        std::vector<Point2D> allPoints = snake_.getAllPoints();
        map_.update(allPoints);
        std::cout << map_.print() << "\n\r";
        getInput(input);
        snake_.turn(input);
        snake_.move(map_);
    }
    std::cout << "GAME OVER" << std::endl;
}

void Game::runContinuous()
{
  map_.print();
  direction input;
  std::thread inputThread(getInputLoop, std::ref(input));

  while(snake_.isAlive())
  {
      if(clock_.duration() > frequency_)
      {
          clock_.reset();
          std::vector<Point2D> allPoints = snake_.getAllPoints();
          map_.update(allPoints);

          std::cout << map_.print() << "\n\r";

          snake_.turn(input);
          snake_.move(map_);
      }
  }
  std::cout << "GAME OVER" << std::endl;
}
