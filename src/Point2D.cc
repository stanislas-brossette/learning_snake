#include <iostream>
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
