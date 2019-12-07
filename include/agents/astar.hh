#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include "Map.hh"
#include "Point2D.hh"
#include "utils.hh"

class AstarNode
{
  public:
    AstarNode(Point2D pos, Point2D target, AstarNode* parent = nullptr);
    Point2D pos_;
    AstarNode* parent_;
    double distFromStart_;
    double distToGoal_;
    double totalDist_;
};

struct SortedListNode
{
  AstarNode* astarNode_;
  SortedListNode* next_;
};

class SortedList
{
  public:
    SortedList(AstarNode* top);
    void insertSorted(AstarNode* newNode);
    SortedListNode* pop();
    SortedListNode* top_;
    void print();
};

direction astar(Map& map, Point2D start, Point2D target);
