#pragma once
#include <curses.h>
#include <stdio.h>
#include <vector>
#include "Enums.hh"
#include "Point2D.hh"

direction inputToDirection(int input);
direction getInput(direction& input);
direction getInputLoop(direction& input);
direction getInputLoopSDL(direction& input, bool& exit);
bool pointInVector(std::vector<Point2D>& v, Point2D& p);
bool compareApples(Point2D p0, Point2D p1);
void sortApples(std::vector<Point2D>& apples, const Point2D& head);
Point2D directionToPoint2D(direction input);
