#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "SDL.h"
#include "snake.h"
#include "spritestexture.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void LoadSprites();
  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::unique_ptr<SpritesTexture> spritesTex = nullptr;
  SDL_Rect snakeSprites[16];

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif