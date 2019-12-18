#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Map.hh"

class Window
{
public:
  Window ();
  Window (const Map& map);
  void render(const Map& map, size_t score);
  ~Window ();

private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  TTF_Font *font_;
  int pixelSize_;
  SDL_Rect scoreRect_;
};

