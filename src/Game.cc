#include <thread>
#include <ctime>
#include "Game.hh"

Game::Game()
  : snake_(direction::right, Point2D(5,5)),
    map_(20,20,2),
    clock_(),
    timeStep_(0.18),
    window_(nullptr),
    displayWindow_(true)
{
    std::vector<Point2D> allPoints = snake_.getAllPoints();
    map_.update(allPoints);
    if(displayWindow_)
    {
      window_ = new Window(map_);
      window_->render(map_, allPoints.size());
    }
}

Game::~Game()
{
  delete window_;
}

Transition Game::step(direction action)
{
  std::cout << "========================================================" << std::endl;
  Transition t;
  getState(t.state);
  t.action = action;

  snake_.turn(action);
  snake_.move(map_);
  std::vector<Point2D> allPoints = snake_.getAllPoints();
  map_.update(allPoints);
  if(displayWindow_)
    window_->render(map_, allPoints.size());

  getState(t.next_state);
  t.reward = snake_.size();
  std::cout << t << std::endl;
  std::cout << "========================================================" << std::endl;
  return t;
}

void Game::getState(State& s)
{
  s.lengthSnake = snake_.size();
  s.directionHead = directionToPoint2D(snake_.head().getDirection());
  // Find closest apple
  std::vector<Point2D> apples = map_.apples();
  sortApples(apples, snake_.head().pos());
  s.directionApple = Point2D(apples[0].x - snake_.head().pos().x, apples[0].y - snake_.head().pos().y);

  //get view
  size_t view_distance = 4;
  size_t view_size = 2*view_distance + 1;
  Point2D v_center = snake_.head().pos();
  Point2D v_top_left(v_center.x - view_distance, v_center.y - view_distance);
  s.view = std::vector<std::vector<status> >(view_size);
  for (size_t i = 0; i < view_size; i++)
  {
    s.view[i] = std::vector<status>(view_size);
    for (size_t j = 0; j < view_size; j++)
    {
      status stat = map_.get(Point2D(v_top_left.x + i, v_top_left.y + j));
      s.view[i][j] = stat;
    }
  }
}

void Game::runStepByStep()
{
  direction input;
  Transition t;
  while(snake_.isAlive())
  {
    getInput(input);
    t = step(input);
  }
  std::cout << "GAME OVER" << std::endl;
  return;
}

//void Game::runStepByStep()
//{
//  direction input;
//  while(snake_.isAlive())
//  {
//    std::vector<Point2D> allPoints = snake_.getAllPoints();
//    map_.update(allPoints);
//    if(displayWindow_)
//      window_->render(map_, allPoints.size());
//    getInput(input);
//    snake_.turn(input);
//    snake_.move(map_);
//  }
//  std::cout << "GAME OVER" << std::endl;
//  return;
//}

void Game::runContinuous()
{
  direction input = direction::down;
  bool exitThread = false;
  std::thread inputThread(getInputLoopSDL, std::ref(input), std::ref(exitThread));

  while(snake_.isAlive())
  {
    if(input == direction::exitGame)
        break;
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
  if (input != direction::exitGame)
      std::cin.get();
  return;
}

size_t Game::runAgent(Agent* agent)
{
    std::cout << "agent: " << agent->name << std::endl;
    direction input;
    direction userInput;
    bool exitThread = false;
    std::thread inputThread(getInputLoopSDL, std::ref(userInput), std::ref(exitThread));
    size_t score = 0;
    timeStep_ = 0.02;
    if(not displayWindow_)
      timeStep_ = 0.0;
    while(snake_.isAlive())
    {
      if(userInput == direction::exitGame)
          break;
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
    exitThread = true;
    inputThread.join();
    std::cout << "Agent scored: " << score << std::endl;
    std::cout << "GAME OVER\npress enter to exit" << std::endl;
    if (userInput != direction::exitGame)
        std::cin.get();
    return score;
}
