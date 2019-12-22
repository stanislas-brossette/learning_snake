#pragma once
#include "Point2D.hh"
#include "Enums.hh"

struct State
{
  std::vector<std::vector<status> > view;
  Point2D directionHead;
  Point2D directionApple;
  int lengthSnake;
};

