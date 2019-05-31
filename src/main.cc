#include <iostream>
#include "Snake.hh"
#include "Enums.hh"
#include "Map.hh"
#include "Point2D.hh"

direction inputToDirection(int input)
{
    switch(input)
    {
        case 2:
            return direction::down;
        case 4:
            return direction::left;
        case 6:
            return direction::right;
        case 8:
            return direction::up;
        default:
            return direction::none;
    }
}

int main(void)
{
    Snake snake(direction::right, Point2D(5,5));
    Map map(20,20);

    int input;
    while(snake.isAlive())
    {
        std::cout << "enter input" << std::endl;
        std::cin >> input;
        snake.turn(inputToDirection(input));
        snake.move(map);
        std::vector<Point2D> allPoints = snake.getAllPoints();
        map.update(allPoints);
        map.print();
    }
    std::cout << "GAME OVER" << std::endl;

    return 0;
}
