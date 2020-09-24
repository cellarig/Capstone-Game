#include "renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // allocate sprites texture
  spritesTex = std::make_unique<SpritesTexture>();
  LoadSprites();
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::LoadSprites() {
  const int clip_width = 16;
  const int clip_height = 16;

  snakeSprites[0] = {0, 0, clip_width, clip_height};   // head up
  snakeSprites[1] = {16, 0, clip_width, clip_height};  // head right
  snakeSprites[2] = {32, 0, clip_width, clip_height};  // head down
  snakeSprites[3] = {48, 0, clip_width, clip_height};  // head left

  snakeSprites[14] = {32, 48, clip_width, clip_height};  // bunny sprites

  spritesTex->loadFromFile("../res/Snake.png", sdl_renderer);
}

void Renderer::Render(Snake const snake, SDL_Point const& food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  spritesTex->render(sdl_renderer, &snakeSprites[14], &block);

  // Render snake's body
  for (SDL_Point const& point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    spritesTex->render(sdl_renderer, &snakeSprites[14], &block);
  }

  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  // for (SDL_Point const &point : snake.body) {
  //   block.x = point.x * block.w;
  //   block.y = point.y * block.h;
  //   SDL_RenderFillRect(sdl_renderer, &block);
  // }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  switch (snake.direction) {
    case Snake::Direction::kUp:
      spritesTex->render(sdl_renderer, &snakeSprites[0], &block);
      break;
    case Snake::Direction::kDown:
      spritesTex->render(sdl_renderer, &snakeSprites[2], &block);
      break;
    case Snake::Direction::kLeft:
      spritesTex->render(sdl_renderer, &snakeSprites[3], &block);
      break;
    case Snake::Direction::kRight:
      spritesTex->render(sdl_renderer, &snakeSprites[1], &block);
      break;
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
