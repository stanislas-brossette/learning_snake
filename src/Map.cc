#include "Map.hh"

Map::Map (int width, int height)
    : width_(width),
      height_(height),
      apple_(width/2, height/2)
{
    content_.resize(height_);
    for (int i = 0; i < height_; i++)
        content_[i].resize(width_);
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
    content_[apple_.x][apple_.y] = status::apple;
}

void Map::set(Point2D p, status s)
{
    content_[p.x][p.y] = s;
}

void Map::print() const
{
    for (int j = 0; j < width_; j++)
        std::cout << "_";
    std::cout << std::endl;
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            switch(content_[i][j])
            {
                case status::obstacle:
                    std::cout << "X";
                    break;
                case status::empty:
                    std::cout << " ";
                    break;
                case status::apple:
                    std::cout << "a";
                    break;
                case status::snake:
                    std::cout << "s";
                    break;
                default:
                    std::cout << "?";
                    break;
            }
        }
        std::cout << std::endl;
    }
    for (int j = 0; j < width_; j++)
        std::cout << "_";
    std::cout << std::endl;
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
