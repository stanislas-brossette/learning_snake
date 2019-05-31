#include <iostream>
#include "Snake.hh"
#include "Enums.hh"
#include "Map.hh"
#include "Point2D.hh"
#include "utils.hh"


int main(void)
{
    Snake snake(direction::right, Point2D(5,5));
    Map map(20,20);

    int input;
    while(snake.isAlive())
    {
        std::vector<Point2D> allPoints = snake.getAllPoints();
        map.update(allPoints);
        map.print();
        std::cout << "enter input" << std::endl;
        std::cin >> input;
        snake.turn(inputToDirection(input));
        snake.move(map);
    }
    std::cout << "GAME OVER" << std::endl;

    return 0;
}
