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
    Map (int width, int height, int nApples);
    std::string print() const;
    virtual ~Map ();
    status get(const Point2D& p) const;
    int getAppleIndex(Point2D loc) const;
    void reset();
    void set(Point2D p, status s);
    void update(std::vector<Point2D>& snake);
    void changeAppleLocation(Point2D loc);
    void changeAppleLocation(int index);
    int width() const {return width_;};
    int height() const {return height_;};
    std::vector<std::vector<status> > content() {return content_;};

private:
    int width_;
    int height_;
    std::vector<std::vector<status> > content_;
    std::vector<Point2D> apples_;
};
