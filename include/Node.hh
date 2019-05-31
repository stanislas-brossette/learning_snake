#pragma once

#include "Point2D.hh"

class Node
{
public:
    Node (const Point2D& pos);
    virtual ~Node ();
    Node* next();
    void update(const Point2D& p);
    void print();
    void setNext(Node* n);
    Point2D pos() const;


protected:
    Node* next_;
    Point2D pos_;
};
