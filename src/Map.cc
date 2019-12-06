#include "Map.hh"
#include "utils.hh"

Map::Map (int width, int height, int nApples)
    : width_(width),
      height_(height),
      apples_(nApples)
{
    content_.resize(height_);
    for (int i = 0; i < height_; i++)
        content_[i].resize(width_);
    resetObstacles();
    for (int i = 0; i < apples_.size(); ++i)
        changeAppleLocation(i);
}

Map::~Map()
{
}

void Map::resetObstacles()
{
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            if (i == 0 || i == height_-1 || j == 0 || j == width_-1)
                content_[i][j] = status::obstacle;
            else
                content_[i][j] = status::empty;
        }
    }
}

void Map::resetApples()
{
    for (int i = 0; i < apples_.size(); ++i)
    {
        content_[apples_[i].x][apples_[i].y] = status::apple;
    }
}

void Map::reset()
{
  resetObstacles();
  resetApples();
}

void Map::set(Point2D p, status s)
{
    content_[p.x][p.y] = s;
}

std::string Map::print() const
{
    std::string mapString = "";
    for (int j = 0; j < width_; j++)
        mapString += "_";
    mapString += "\n\r";
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            switch(content_[i][j])
            {
                case status::obstacle:
                    mapString += "X";
                    break;
                case status::empty:
                    mapString += " ";
                    break;
                case status::apple:
                    mapString += "a";
                    break;
                case status::snake:
                    mapString += "s";
                    break;
                case status::snake_head:
                    mapString += "S";
                    break;
                default:
                    mapString += "?";
                    break;
            }
        }
        mapString += "\n\r";
    }
    for (int j = 0; j < width_; j++)
        mapString += "_";
    mapString += "\n\r";
    return mapString;
}

status Map::get(const Point2D& p) const
{
    return content_.at(p.x).at(p.y);
}

bool Map::isFree(const Point2D& p) const
{
    status s = content_.at(p.x).at(p.y);
    if(s == status::empty or s == status::apple)
        return true;
    else
        return false;
}

size_t Map::computeFreeArea(const Point2D& p0) const
{
  std::vector<Point2D> visitedNodes;
  if(isFree(p0))
      visitedNodes.push_back(p0);
  else
      return 0;

  size_t i = 0;
  while(i < visitedNodes.size())
  {
      Point2D p = visitedNodes[i];
      std::vector<Point2D> neighbors;
      Point2D pUp(p.x,p.y-1);
      Point2D pDown(p.x,p.y+1);
      Point2D pRight(p.x+1,p.y);
      Point2D pLeft(p.x-1,p.y);
      neighbors.push_back(pUp);
      neighbors.push_back(pDown);
      neighbors.push_back(pRight);
      neighbors.push_back(pLeft);
      for (size_t i = 0; i < neighbors.size(); i++)
      {
        if(not pointInVector(visitedNodes, neighbors[i])
            and isFree(neighbors[i]))
        {
          visitedNodes.push_back(neighbors[i]);
        }
      }
      ++i;
  }
  return visitedNodes.size();
}

void Map::update(std::vector<Point2D>& s)
{
    reset();
    if(s.size() >= 1)
    {
      set(s[0], status::snake_head);
      for (int i = 1; i < s.size(); i++)
          set(s[i], status::snake);
    }
}

int Map::getAppleIndex(Point2D loc) const
{
    for (int i = 0; i < apples_.size(); ++i)
    {
        if(apples_[i].x == loc.x && apples_[i].y == loc.y)
        {
            return i;
        }
    }
    return -1;
}

void Map::changeAppleLocation(int index)
{
    if(index == -1)
        return;
    int i = 0;
    int j = 0;
    while(true)
    {
        i = std::rand()%height_;
        j = std::rand()%width_;
        if(content_[i][j] == status::empty)
        {
            apples_[index].x = i;
            apples_[index].y = j;
            break;
        }
    }
    resetApples();
}

void Map::changeAppleLocation(Point2D loc)
{
    int index = getAppleIndex(loc);
    changeAppleLocation(index);
}
