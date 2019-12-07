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

direction AStarAgent::decide(Map& map, Snake& snake)
{
    // Find closest apple
    std::vector<Point2D> apples = map.apples();

    // Sort apples
    sortApples(apples, snake.head().pos());

    // Astar
    direction dir = direction::none;
    for (size_t i = 0; i < apples.size(); i++)
    {
      dir = astar(map, snake.head().pos(), apples[i]);
      if(dir != direction::none)
        return dir;
    }

    // Astar failed; backup strat
    Point2D pLeft(snake.head().pos().x, snake.head().pos().y-1);
    Point2D pRight(snake.head().pos().x, snake.head().pos().y+1);
    Point2D pDown(snake.head().pos().x+1, snake.head().pos().y);
    Point2D pUp(snake.head().pos().x-1, snake.head().pos().y);

    size_t nLeft = map.computeFreeArea(pLeft);
    size_t nRight = map.computeFreeArea(pRight);
    size_t nUp = map.computeFreeArea(pUp);
    size_t nDown = map.computeFreeArea(pDown);

    if(nUp >= nRight and nUp >= nLeft and nUp >= nDown)
        return direction::up;
    else if(nDown >= nRight and nDown >= nLeft and nDown >= nUp)
        return direction::down;
    else if(nRight >= nUp and nRight >= nLeft and nRight >= nDown)
        return direction::right;
    else if(nLeft >= nRight and nLeft >= nUp and nLeft >= nDown)
        return direction::left;
    else
        return direction::none;
}
