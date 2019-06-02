#include <iostream>
#include "Node.hh"

Node::Node(const Point2D& pos)
    : next_(nullptr),
      pos_(pos)
{
}

Node::~Node()
{}

Node* Node::next()
{
    return next_;
}

void Node::update(const Point2D& p)
{
    if(next_)
        next_->update(pos_);
    pos_ = p;
}

void Node::print()
{
    pos_.print();
    if(next_)
        next_->print();
    else
        std::cout << "\n\r";

}

void Node::setNext(Node* n)
{
    next_ = n;
}

Point2D Node::pos() const
{
    return pos_;
}
