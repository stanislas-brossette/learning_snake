#include <iostream>
#include "Head.hh"

Head::Head (const direction& dir, const Point2D& pos)
    : Node(pos),
      dir_(dir)
{
}

Head::~Head()
{}

Point2D Head::advance() const
{
    Point2D newPos = pos_;
    switch(dir_)
    {
        case right:
            newPos.y += 1;
            break;
        case left:
            newPos.y -= 1;
            break;
        case up:
            newPos.x -= 1;
            break;
        case down:
            newPos.x += 1;
            break;
    }
    return newPos;
}


void Head::follow(const Point2D& newPos)
{
    if(next_)
        next_->update(pos_);
    pos_ = newPos;
}

void Head::grow(const Point2D& newPos)
{
    Node* newNode = new Node(pos_);
    newNode->setNext(next_);
    next_ = newNode;
    pos_ = newPos;
}

void Head::setDirection(const direction& dir)
{
    dir_ = dir;
}

direction Head::getDirection()
{
    return dir_;
}
