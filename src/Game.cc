#include "Game.hh"
#include <thread>
#include <ctime>

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
        getInput(input);
        snake.turn(input);
        snake.move(map);
    }
    std::cout << "GAME OVER" << std::endl;
}

void Game::runContinuous(double frequency)
{
  std::clock_t start;
  start = std::clock();
  double duration;
  direction input;
  std::thread inputThread(getInputLoop, std::ref(input));

  Snake snake(direction::right, Point2D(5,5));
  Map map(40,40);
  while(snake.isAlive())
  {
      duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
      if(duration > frequency)
      {
          start = std::clock();
          std::vector<Point2D> allPoints = snake.getAllPoints();
          map.update(allPoints);

          std::string mapString;
          mapString = map.print();
          std::cout << mapString << std::endl;

          snake.turn(input);
          snake.move(map);
      }
  }
  std::cout << "GAME OVER" << std::endl;
}
