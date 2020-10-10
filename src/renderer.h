#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "SDL.h"
#include "snake.h"
#include "texture.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const &snake, SDL_Point const &bunny);
  void UpdateWindowTitle(int score, int fps);

 private:
  void Init();
  void InitTextures();
  void ConfigureClips();
  void RenderSnake(Snake const &snake);
  void RenderBunny(SDL_Point const &bunny);
  void RenderRoad();

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::unique_ptr<SpritesTexture> spritesTex = nullptr;
  std::unique_ptr<JpgImageTexture> jpgTex = nullptr;

  SDL_Rect snake_sprites[16];
  SDL_Rect render_block;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif