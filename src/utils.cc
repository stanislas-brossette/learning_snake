#include "utils.hh"

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
