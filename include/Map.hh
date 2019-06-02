#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "Enums.hh"
#include "Point2D.hh"


class Map
{
public:
    Map (int width, int height);
    std::string print() const;
    virtual ~Map ();
    status get(const Point2D& p) const;
    void reset();
    void set(Point2D p, status s);
    void update(std::vector<Point2D>& snake);
    void changeAppleLocation();

private:
    int width_;
    int height_;
    std::vector<std::vector<status> > content_;
    Point2D apple_;
};
