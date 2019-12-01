#include <bits/stdc++.h>
#include "agents/Agent.hh"

Agent::Agent()
  : name("GenericAgent")
{
}

RandomAgent::RandomAgent()
{
  name = "RandomAgent";
}

direction RandomAgent::decide(Map& map, Snake& snake)
{
    direction d = static_cast<direction>(std::rand() % direction::none);
    return d;
}

DirectAgent::DirectAgent()
{
  name = "DirectAgent";
}

direction DirectAgent::decide(Map& map, Snake& snake)
{
    //Find closest apple
    std::vector<Point2D> apples = map.apples();
    Point2D headPos = snake.head().pos();
    Point2D closestApple;
    double minDist = -1;
    for (size_t i = 0; i < apples.size(); ++i)
    {
        double d = headPos.squaredDist(apples[i]);
        if( minDist < 0 or d < minDist)
        {
            minDist = d;
            closestApple = apples[i];
        }
    }
    Point2D vec(closestApple.x - headPos.x, closestApple.y - headPos.y);
    if (vec.x + vec.y >= 0 and vec.x - vec.y > 0)
        return direction::down;
    else if (vec.x + vec.y >= 0 and vec.x - vec.y < 0)
        return direction::right;
    else if (vec.x + vec.y < 0 and vec.x - vec.y >= 0)
        return direction::left;
    else if (vec.x + vec.y < 0 and vec.x - vec.y <= 0)
        return direction::up;
    else
        return direction::none;
}

AStarAgent::AStarAgent()
{
  name = "AStarAgent";
}

bool compareApples(Point2D p0, Point2D p1)
{
  if (p0.x*p0.x+p0.y*p0.y < p1.x*p1.x+p1.y*p1.y)
    return true;
  else
    return false;
}

direction AStarAgent::decide(Map& map, Snake& snake)
{
    //Find closest apple
    std::vector<Point2D> apples = map.apples();
    Point2D headPos = snake.head().pos();
    //Point2D closestApple;
    //double minDist = -1;
    //for (size_t i = 0; i < apples.size(); ++i)
    //{
    //    double d = headPos.squaredDist(apples[i]);
    //    if( minDist < 0 or d < minDist)
    //    {
    //        minDist = d;
    //        closestApple = apples[i];
    //    }
    //}

    //// Sort apples
    std::vector<Point2D> headToApples = apples;
    for (size_t i = 0; i < headToApples.size(); i++)
    {
      headToApples[i].x -= headPos.x;
      headToApples[i].y -= headPos.y;
    }

    std::sort(headToApples.begin(), headToApples.end(), compareApples);

    for (size_t i = 0; i < headToApples.size(); i++)
    {
      headToApples[i].x += headPos.x;
      headToApples[i].y += headPos.y;
    }

    direction dir = direction::none;
    for (size_t i = 0; i < headToApples.size(); i++)
    {
      dir = astar(map, headPos, headToApples[i]);
      if(dir != direction::none)
        return dir;
    }

    return direction::none;
}
