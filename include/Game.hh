#pragma once
#include "Snake.hh"
#include "Enums.hh"
#include "Map.hh"
#include "Point2D.hh"
#include "utils.hh"

class Game
{
public:
  Game ();
  virtual ~Game ();
  void runStepByStep();
  void runContinuous();
};
