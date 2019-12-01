#include <iostream>
#include <cmath>
#include "Point2D.hh"

Point2D::Point2D(int x, int y)
    : x(x), y(y)
{
}

Point2D::Point2D(const Point2D& p)
    : x(p.x), y(p.y)
{
}

void Point2D::print()
{
    std::cout << "(" << x << "," << y << ")";
}

double Point2D::squaredDist(const Point2D& p)
{
    double d = (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
    return d;
}

double Point2D::dist(const Point2D& p)
{
    double d2 = squaredDist(p);
    double d = std::sqrt(d2);
    return d;
}

bool Point2D::operator == (const Point2D& p) const
{
  if(p.x == x and p.y == y)
    return true;
  else
    return false;
}

direction Point2D::directionToGo(const Point2D& p) const
{
  if(p.x == x && p.y == y + 1)
  {
    return direction::right;
  }
  else if(p.x == x && p.y == y - 1)
  {
    return direction::left;
  }
  else if(p.x == x + 1 && p.y == y)
  {
    return direction::down;
  }
  else if(p.x == x - 1 && p.y == y)
  {
    return direction::up;
  }
  else
  {
    std::cout << "error, points are not neighbors" << std::endl;
    return direction::none;
  }
}
