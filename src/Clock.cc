#include "Clock.hh"

Clock::Clock()
{
  reset();
}

void Clock::reset()
{
  start = std::clock();
}

double Clock::duration()
{
    return ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}
