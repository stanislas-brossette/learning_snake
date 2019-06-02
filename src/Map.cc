#include "Map.hh"

Map::Map (int width, int height, int nApples)
    : width_(width),
      height_(height),
      apples_(nApples)
{
    content_.resize(height_);
    for (int i = 0; i < height_; i++)
        content_[i].resize(width_);
    for (int i = 0; i < apples_.size(); ++i)
        changeAppleLocation(i);
    reset();
}

Map::~Map()
{
}

void Map::reset()
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
    for (int i = 0; i < apples_.size(); ++i)
    {
        content_[apples_[i].x][apples_[i].y] = status::apple;
    }
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

void Map::update(std::vector<Point2D>& s)
{
    reset();
    for (int i = 0; i < s.size(); i++)
        set(s[i], status::snake);
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
            return;
        }
    }
}

void Map::changeAppleLocation(Point2D loc)
{
    int index = getAppleIndex(loc);
    changeAppleLocation(index);
}
