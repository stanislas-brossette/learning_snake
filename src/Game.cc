#include "Game.hh"
#include <thread>
#include <ctime>

Game::Game()
  : snake_(direction::right, Point2D(5,5)),
    map_(40,40,3),
    clock_(),
    frequency_(0.18),
    window_(map_)
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
        window_.render(map_, allPoints.size());
        //std::cout << map_.print() << "\n\r";
        getInput(input);
        snake_.turn(input);
        snake_.move(map_);
    }
    std::cout << "GAME OVER" << std::endl;
    return;
}

void Game::runContinuous()
{
  map_.print();
  direction input = direction::down;
  bool exitThread = false;
  std::thread inputThread(getInputLoopSDL, std::ref(input), std::ref(exitThread));

  while(snake_.isAlive())
  {
      if(clock_.duration() > frequency_)
      {
          clock_.reset();
          std::vector<Point2D> allPoints = snake_.getAllPoints();
          map_.update(allPoints);
          window_.render(map_, allPoints.size());

          //std::cout << map_.print() << "\n\r";

          snake_.turn(input);
          snake_.move(map_);
      }
  }
  exitThread = true;
  inputThread.join();
  std::cout << "GAME OVER\npress enter to exit" << std::endl;
  std::cin.get();
  return;
}
