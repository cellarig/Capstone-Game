#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const char *window_title, const std::size_t screen_width,
           const std::size_t screen_height, const std::size_t grid_width,
           const std::size_t grid_height);
  ~Renderer();

  SDL_Texture *LoadTexture(const char *filePath);

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateScore(int score, int fps);

 private:
  void RenderSnakeHead(Snake const snake);

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface *screen_surface;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif