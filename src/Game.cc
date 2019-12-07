#include "Game.hh"
#include <thread>
#include <ctime>

Game::Game()
  : snake_(direction::right, Point2D(5,5)),
    map_(90,50,30),
    clock_(),
    timeStep_(0.18),
    window_(nullptr),
    displayWindow_(true)
{
    if(displayWindow_)
      window_ = new Window(map_);
}

Game::~Game()
{
  delete window_;
}

void Game::runStepByStep()
{
  direction input;
  while(snake_.isAlive())
  {
    std::vector<Point2D> allPoints = snake_.getAllPoints();
    map_.update(allPoints);
    if(displayWindow_)
      window_->render(map_, allPoints.size());
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
    if(clock_.duration() > timeStep_)
    {
      clock_.reset();
      std::vector<Point2D> allPoints = snake_.getAllPoints();
      map_.update(allPoints);
      if(displayWindow_)
        window_->render(map_, allPoints.size());
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
    timeStep_ = 0.02;
    if(not displayWindow_)
      timeStep_ = 0.0;
    while(snake_.isAlive())
    {
      if(clock_.duration() >= timeStep_)
      {
        clock_.reset();
        std::vector<Point2D> allPoints = snake_.getAllPoints();
        map_.update(allPoints);
        score = allPoints.size();
        if(displayWindow_)
          window_->render(map_, score);
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
