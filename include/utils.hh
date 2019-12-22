#pragma once
#include <curses.h>
#include <stdio.h>
#include <vector>
#include "Enums.hh"
#include "Point2D.hh"
#include "Map.hh"
#include "State.hh"
#include "Transition.hh"

direction inputToDirection(int input);
direction getInput(direction& input);
direction getInputLoop(direction& input);
direction getInputLoopSDL(direction& input, bool& exit);
bool pointInVector(std::vector<Point2D>& v, Point2D& p);
bool compareApples(Point2D p0, Point2D p1);
void sortApples(std::vector<Point2D>& apples, const Point2D& head);
Point2D directionToPoint2D(direction input);

std::ostream &operator<<(std::ostream &os, direction const &d);
std::ostream &operator<<(std::ostream &os, status const &s);
std::ostream &operator<<(std::ostream &os, Point2D const &p);
std::ostream &operator<<(std::ostream &os, std::vector<status> const &s);
std::ostream &operator<<(std::ostream &os, std::vector<std::vector<status> > const &s);
std::ostream &operator<<(std::ostream &os, Map &m);
std::ostream &operator<<(std::ostream &os, State &s);
std::ostream &operator<<(std::ostream &os, Transition &t);
