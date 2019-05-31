#pragma once
#include <iostream>
#include <vector>
#include "Enums.hh"
#include "Point2D.hh"


class Map
{
public:
    Map (int width, int height);
    void print() const;
    virtual ~Map ();
    status get(const Point2D& p) const;
    void reset();
    void set(Point2D p, status s);
    void update(std::vector<Point2D>& snake);

private:
    int width_;
    int height_;
    std::vector<std::vector<status> > content_;
    Point2D apple_;
};
