#include <iostream>
#include "utils.hh"
#include "Enums.hh"

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

direction getInputLoop(direction& res)
{
    while(true)
    {
        getInput(res);
    }
}

direction getInput(direction& res)
{
    int ch = 0;

    /* Basic initialization of curses lib */
    initscr();
    cbreak();
    noecho(); /* Set this for interactive programs. */
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    /* Ready to rumble! */
    //printw("Type a key. Use 'q' to quit\n");
    ch = getch();
    res = direction::none;
    if( (char) ch == '4' || ch == 260 || (char) ch == 'a')
      res = direction::left;
    else if( (char) ch == '6' || ch == 261 || (char) ch == 'd')
      res = direction::right;
    else if( (char) ch == '5' || (char) ch == '2' || ch == 258 || (char) ch == 's')
      res = direction::down;
    else if( (char) ch == '8' || ch == 259 || (char) ch == 'w')
      res = direction::up;

    //switch( (char) ch)
    //{
    //  case '4':
    //    res = direction::left;
    //    break;
    //  case '6':
    //    res = direction::right;
    //    break;
    //  case '2':
    //    res = direction::down;
    //    break;
    //  case '5':
    //    res = direction::down;
    //    break;
    //  case '8':
    //    res = direction::up;
    //    break;
    //}
    //while (ch != 'q') {
    //    ch = getch();
    //printw("You typed: '%c' which is ASCII %d\n", (char) ch, ch);
    //}

    /* Cleanup time */
    endwin();
    return res;
}
