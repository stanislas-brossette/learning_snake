#pragma once

struct Point2D
{
    Point2D(int x = 0, int y = 0);
    Point2D(const Point2D& p);
    double squaredDist(const Point2D& p);
    int x;
    int y;
    void print();
};
