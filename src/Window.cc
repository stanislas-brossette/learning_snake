#include "Window.hh"
#include "Enums.hh"
#include <iostream>

Window::Window(const Map& map):
  window_(nullptr),
  renderer_(nullptr),
  pixelSize_(20),
  scoreRect_({0, pixelSize_*map.height(), 100, 20})
{
	Uint32 flags = SDL_WINDOW_SHOWN;

	// Set up window
	window_ = SDL_CreateWindow("learning_snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pixelSize_*map.width(), pixelSize_*map.height() + 20, flags);
	if(!window_) {
		std::cerr << SDL_GetError() << std::endl;
	}

	// Set up renderer
	flags = 0;
	flags |= SDL_RENDERER_ACCELERATED;
	renderer_ = SDL_CreateRenderer(window_, -1, flags);
	if(renderer_ == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
	}
  TTF_Init();
  const char* fontPath = "/home/stanislas/profiles/devel/src/learning_snake/assets/arimo_regular.ttf";
  font_ = TTF_OpenFont(fontPath, 12);

}

void Window::render(const Map& map, size_t score)
{
	// Clear screen
	SDL_RenderClear(renderer_);
  SDL_Rect fillRect_;
  for(int i = 0; i < map.height(); ++i)
  {
    for (int j = 0; j < map.width(); ++j)
    {
      fillRect_ = {pixelSize_*j+1, pixelSize_*i+1, pixelSize_-2, pixelSize_-2};
      status s = map.get(Point2D(i,j));
      switch (s) {
        case obstacle:
          SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
          break;
        case apple:
          SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0x00, 0xFF);
          break;
        case snake:
          SDL_SetRenderDrawColor(renderer_, 0x00, 0xFF, 0x00, 0xFF);
          break;
        default:
          SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
          break;
      }
      SDL_RenderFillRect(renderer_, &fillRect_);
    }
  }

  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);

  // Render score
  TTF_Init();
  SDL_Color textColor = {255, 0, 255, 0};
  std::string text_s = "Score: " + std::to_string(score);
  const char* text_c = text_s.c_str();
  SDL_Surface* surface = TTF_RenderText_Solid(font_, text_c, textColor);
  SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_RenderCopy(renderer_, texture1, NULL, &scoreRect_);
	// Render to screen
	SDL_RenderPresent(renderer_);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
  std::cout << "Window closed" << std::endl;
}
