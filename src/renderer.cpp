#include "renderer.h"

#include <iostream>
#include <string>

#include "spritesheet.h"

Renderer::Renderer(const char* window_title, const std::size_t screen_width,
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
  sdl_window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED,
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

  // Get window surface
  if (nullptr != sdl_window) {
    screen_surface = SDL_GetWindowSurface(sdl_window);
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_FreeSurface(screen_surface);
  SDL_Quit();
}

SDL_Texture* Renderer::LoadTexture(const char* filePath) {
  SDL_Texture* texture = nullptr;
  texture = IMG_LoadTexture(sdl_renderer, filePath);
  if (texture == nullptr)
    std::cerr << "Failed to load texture. SDL_Error: " << SDL_GetError()
              << "\n";
  return texture;
}

void Renderer::Render(Snake const snake, SDL_Point const& food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const& point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  // RenderSnakeHead(snake);
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderSnakeHead(Snake const snake) {
  int row, column;

  switch (snake.direction) {
    case Entity::Direction::kLeft:
      row = 0;
      column = 3;
      break;
    case Entity::Direction::kRight:
      row = 0;
      column = 1;
      break;
    case Entity::Direction::kDown:
      row = 0;
      column = 2;
      break;
    default:
      row = 0;
      column = 0;
      break;
  }

  Spritesheet sprites("res/snake.png", row, column);
  SDL_Rect head_rect;
  head_rect.w = screen_width / grid_width;
  head_rect.h = screen_height / grid_height;
  head_rect.x = static_cast<int>(snake.head_x) * head_rect.w;
  head_rect.y = static_cast<int>(snake.head_y) * head_rect.h;
  sprites.draw_selected_sprite(screen_surface, &head_rect);
}

void Renderer::UpdateScore(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  // FIXME
  // SDL_SetWindowTitle(sdl_window, title.c_str());
}
