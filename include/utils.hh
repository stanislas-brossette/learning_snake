#pragma once
#include <curses.h>
#include <stdio.h>
#include "Enums.hh"

direction inputToDirection(int input);
direction getInput(direction& input);
direction getInputLoop(direction& input);
direction getInputLoopSDL(direction& input);
