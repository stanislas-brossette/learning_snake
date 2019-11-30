#pragma once

#include "Head.hh"
#include "Enums.hh"
#include "Point2D.hh"
#include "Map.hh"

class Snake
{
public:
    Snake (const direction& dir, const Point2D& pos);
    virtual ~Snake ();
    bool isAlive() const;
    void move(Map& map);
    void turn(direction dir);
    void show();
    std::vector<Point2D> getAllPoints();
    Head head(){return head_;};


private:
    bool alive_;
    Head head_;
};
