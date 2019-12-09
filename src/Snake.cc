#include <iostream>
#include "Snake.hh"

Snake::Snake(const direction& dir, const Point2D& pos)
    : head_(dir, pos),
      alive_(true),
      size_(1)
{
}

Snake::~Snake()
{
}

bool Snake::isAlive() const
{
    return alive_;
}

void Snake::move(Map& map)
{
    Point2D newHeadPos = head_.advance();
    status newTileStatus = map.get(newHeadPos);
    switch(newTileStatus)
    {
        case status::empty:
            head_.follow(newHeadPos);
            break;
        case status::apple:
            head_.grow(newHeadPos);
            size_++;
            map.changeAppleLocation(newHeadPos);
            break;
        case status::obstacle:
        case status::snake:
            alive_ = false;
            head_.follow(newHeadPos);
            break;
    }
}

void Snake::turn(direction newDir)
{
    switch(newDir)
    {
        case direction::right :
            if(head_.getDirection() != direction::left or size_ == 1)
                head_.setDirection(newDir);
            break;
        case direction::left :
            if(head_.getDirection() != direction::right or size_ == 1)
                head_.setDirection(newDir);
            break;
        case direction::up :
            if(head_.getDirection() != direction::down or size_ == 1)
                head_.setDirection(newDir);
            break;
        case direction::down :
            if(head_.getDirection() != direction::up or size_ == 1)
                head_.setDirection(newDir);
            break;
        case direction::none:
            break;
    }
}

void Snake::show()
{
    head_.print();
}

std::vector<Point2D> Snake::getAllPoints()
{
    std::vector<Point2D> points(0);
    points.push_back(head_.pos());
    Node* next = head_.next();
    while(next)
    {
        points.push_back(next->pos());
        next = next->next();
    }
    return points;
}
