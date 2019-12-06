#include "Game.hh"
#include <thread>
#include <ctime>

Game::Game()
  : snake_(direction::right, Point2D(5,5)),
    map_(90,50,27),
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

size_t Game::runAgent(Agent* agent)
{
    std::cout << "agent: " << agent->name << std::endl;
    direction input;
    size_t score = 0;
    frequency_ = 0.02;
    while(snake_.isAlive())
    {
        if(clock_.duration() > frequency_)
        {
            clock_.reset();
            std::vector<Point2D> allPoints = snake_.getAllPoints();
            map_.update(allPoints);
            score = allPoints.size();
            window_.render(map_, score);
            input = agent->decide(map_, snake_);
            snake_.turn(input);
            snake_.move(map_);
        }
    }
    std::cout << "Agent scored: " << score << std::endl;
    std::cout << "GAME OVER\npress enter to exit" << std::endl;
    std::cin.get();
    return score;
}
