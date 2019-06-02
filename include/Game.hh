#pragma once
#include "Snake.hh"
#include "Enums.hh"
#include "Map.hh"
#include "Point2D.hh"
#include "utils.hh"
#include "Clock.hh"

class Game
{
public:
  Game ();
  virtual ~Game ();
  void runStepByStep();
  void runContinuous();
private:
  Map map_;
  Snake snake_;
  direction input_;
  Clock clock_;
  double frequency_;
};
