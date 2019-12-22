#pragma once
#include "Snake.hh"
#include "agents/Agent.hh"
#include "Enums.hh"
#include "Map.hh"
#include "Point2D.hh"
#include "utils.hh"
#include "Clock.hh"
#include "Window.hh"
#include "Transition.hh"
#include "State.hh"

class Game
{
public:
  Game ();
  virtual ~Game ();
  Transition step(direction action);
  void getState(State& s);
  void runStepByStep();
  void runContinuous();
  size_t runAgent(Agent* agent);
private:
  Map map_;
  Snake snake_;
  direction input_;
  Clock clock_;
  Window* window_;
  double timeStep_;
  bool displayWindow_;
};
