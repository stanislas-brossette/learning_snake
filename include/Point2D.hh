#pragma once
#include "Enums.hh"
#include <functional>

struct Point2D
{
    Point2D(int x = 0, int y = 0);
    Point2D(const Point2D& p);
    double squaredDist(const Point2D& p);
    double dist(const Point2D& p);
    int x;
    int y;
    void print();
    bool operator == (const Point2D& p) const;
    direction directionToGo(const Point2D& p) const;
    void normalize();
};

template<> struct std::hash<Point2D>
{
  size_t operator()(const Point2D& p) const
  {
    return std::hash<int>()(p.x*10000+p.y);
  }
};
