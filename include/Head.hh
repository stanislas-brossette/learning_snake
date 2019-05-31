#pragma once

#include "Node.hh"
#include "Enums.hh"

class Head : public Node
{
public:
    Head (const direction& dir, const Point2D& pos);
    virtual ~Head ();
    Point2D advance() const;
    void follow(const Point2D& newPos);
    void grow(const Point2D& newPos);
    void setDirection(const direction& dir);
    direction getDirection();

private:
    direction dir_;
};
