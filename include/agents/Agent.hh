#pragma once
#include "Map.hh"
#include "Snake.hh"
#include "Enums.hh"
#include "agents/astar.hh"

class Agent
{
public:
  Agent ();
  virtual direction decide(Map& map, Snake& snake) = 0;
  std::string name;
};

class RandomAgent: public Agent
{
public:
  RandomAgent();
  direction decide(Map& map, Snake& snake);
};

class DirectAgent: public Agent
{
public:
  DirectAgent();
  direction decide(Map& map, Snake& snake);
};

class AStarAgent: public Agent
{
public:
  AStarAgent();
  direction decide(Map& map, Snake& snake);
};

// AStarAgent
// GeneticAgent
// DLAgent

