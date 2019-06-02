#pragma once
#include <ctime>

class Clock
{
public:
  Clock ();
  void reset();
  double duration();

private:
  std::clock_t start;
};
