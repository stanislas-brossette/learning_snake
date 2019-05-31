#include <iostream>
#include "Snake.hh"

Snake::Snake(const direction& dir, const Point2D& pos)
    : head_(dir, pos),
      alive_(true)
{
}

Snake::~Snake()
{
}

bool Snake::isAlive() const
{
    return alive_;
}

void Snake::move(const Map& map)
{
    std::cout << "move" << std::endl;
    Point2D newHeadPos = head_.advance();
    status newTileStatus = map.get(newHeadPos);
    switch(newTileStatus)
    {
        case status::empty:
            head_.follow(newHeadPos);
            break;
        case status::apple:
            std::cout << "eating apple" << std::endl;
            newHeadPos.print();
            head_.grow(newHeadPos);
            break;
        case status::obstacle:
        case status::snake:
            alive_ = false;
            head_.follow(newHeadPos);
            break;
    }
    show();
}

void Snake::turn(direction newDir)
{
    std::cout << "turn ";
    switch(newDir)
    {
        case direction::right :
            std::cout << "right" << std::endl;
            if(head_.getDirection() != direction::left)
                head_.setDirection(newDir);
            break;
        case direction::left :
            std::cout << "left" << std::endl;
            if(head_.getDirection() != direction::right)
                head_.setDirection(newDir);
            break;
        case direction::up :
            std::cout << "up" << std::endl;
            if(head_.getDirection() != direction::down)
                head_.setDirection(newDir);
            break;
        case direction::down :
            std::cout << "down" << std::endl;
            if(head_.getDirection() != direction::up)
                head_.setDirection(newDir);
            break;
        case direction::none:
            break;
        default:
            std::cout << "ERROR: wrong way" << std::endl;
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