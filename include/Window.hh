#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Map.hh"

class Window
{
public:
  Window (const Map& map);
  void render(const Map& map);
  ~Window ();

private:
	SDL_Window *window_;
  SDL_Renderer *renderer_;
  int pixelSize_;
};

