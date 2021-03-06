#include <iostream>
#include <ostream>
#include <SDL.h>
#include <bits/stdc++.h>

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

direction getInputLoopSDL(direction& res, bool& exit)
{
  SDL_Event event;
  while(not exit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_KEYDOWN)
      {
        std::string keyName = SDL_GetKeyName(event.key.keysym.sym);
        if(keyName == "Down" or keyName == "J")
            res = direction::down;
        else if(keyName == "Right" or keyName == "L")
            res = direction::right;
        else if(keyName == "Up" or keyName == "K")
            res = direction::up;
        else if(keyName == "Left" or keyName == "H")
            res = direction::left;
        else if(keyName == "Escape")
            res = direction::exitGame;
        else
            res = direction::none;
      }
      else if (event.type == SDL_WINDOWEVENT)
      {
          if(event.window.event == SDL_WINDOWEVENT_CLOSE)
              res = direction::exitGame;
      }
    }
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

    /* Cleanup time */
    endwin();
    return res;
}

bool pointInVector(std::vector<Point2D>& v, Point2D& p)
{
  for (size_t i = 0; i < v.size(); i++)
  {
    if(p.x == v[i].x and p.y == v[i].y)
      return true;
  }
  return false;
}

void sortApples(std::vector<Point2D>& apples, const Point2D& headPos)
{
    for (size_t i = 0; i < apples.size(); i++)
    {
      apples[i].x -= headPos.x;
      apples[i].y -= headPos.y;
    }

    std::sort(apples.begin(), apples.end(), compareApples);

    for (size_t i = 0; i < apples.size(); i++)
    {
      apples[i].x += headPos.x;
      apples[i].y += headPos.y;
    }
}

bool compareApples(Point2D p0, Point2D p1)
{
  if (p0.x*p0.x+p0.y*p0.y < p1.x*p1.x+p1.y*p1.y)
    return true;
  else
    return false;
}

Point2D directionToPoint2D(direction input)
{
  Point2D p;
  switch(input)
  {
    case direction::right:
      p.x = 0;
      p.y = 1;
      break;
    case direction::left:
      p.x = 0;
      p.y = -1;
      break;
    case direction::up:
      p.x = -1;
      p.y = 0;
      break;
    case direction::down:
      p.x = 1;
      p.y = 0;
      break;
  }
  return p;
}

std::ostream &operator<<(std::ostream &os, direction const &d)
{
  switch(d)
  {
    case direction::right:
      return os << "right";
    case direction::left:
      return os << "left";
    case direction::up:
      return os << "up";
    case direction::down:
      return os << "down";
    case direction::none:
      return os << "none";
    case direction::exitGame:
      return os << "exitGame";
  }
}

std::ostream &operator<<(std::ostream &os, status const &s)
{
  switch(s)
  {
    case status::empty:
      return os << " ";
    case status::obstacle:
      return os << "X";
    case status::apple:
      return os << "o";
    case status::snake:
      return os << "s";
    case status::snake_head:
      return os << "S";
  }
}

std::ostream &operator<<(std::ostream &os, Point2D const &p) {
    return os << "(" << p.x << "," << p.y << ")";
}

std::ostream &operator<<(std::ostream &os, std::vector<status> const &s)
{
  if(s.size() == 0)
    return os << "empty";
  for (size_t i = 0; i < s.size(); i++)
  {
    os << s.at(i);
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, std::vector<std::vector<status> > const &s)
{
  if(s.size() == 0)
    return os << "empty";
  for (size_t i = 0; i < s.size(); i++)
  {
    os << s.at(i) << std::endl;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, Map &m)
{
  return os << m.content();
}

std::ostream &operator<<(std::ostream &os, State &s)
{
  os << "directionHead: " << s.directionHead << std::endl;
  os << "directionApple: " << s.directionApple << std::endl;
  os << "lengthSnake: " << s.lengthSnake << std::endl;
  os << "view: \n" << s.view << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, Transition &t)
{
  os << "state: \n" << t.state << std::endl;
  os << "action: " << t.action << std::endl;
  os << "next_state: \n" << t.next_state << std::endl;
  os << "reward: " << t.reward << std::endl;
}
