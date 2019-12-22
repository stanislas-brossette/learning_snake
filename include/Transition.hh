#pragma once
#include <iostream>
#include "State.hh"
#include "Enums.hh"

struct Transition
{
  State state;
  direction action;
  State next_state;
  double reward;
};

