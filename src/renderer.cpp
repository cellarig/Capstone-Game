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
  // SDL init
  Init();

  // allocate textures
  InitTextures();
  ConfigureClips();
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Init() {
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

  // init render block
  render_block.w = screen_width / grid_width;
  render_block.h = screen_height / grid_height;
}

void Renderer::InitTextures() {
  // allocate textures
  spritesTex = std::make_unique<SpritesTexture>();
  jpgTex = std::make_unique<JpgImageTexture>();

  spritesTex->LoadFromFile("../res/Snake.png", sdl_renderer);
  jpgTex->LoadFromFile("../res/road.jpg", sdl_renderer);
}

void Renderer::ConfigureClips() {
  const int clip_width = 16;
  const int clip_height = 16;

  snake_sprites[0] = {0, 0, clip_width, clip_height};   // head up
  snake_sprites[1] = {16, 0, clip_width, clip_height};  // head right
  snake_sprites[2] = {32, 0, clip_width, clip_height};  // head down
  snake_sprites[3] = {48, 0, clip_width, clip_height};  // head left

  snake_sprites[4] = {0, 16, clip_width, clip_height};   // tail up
  snake_sprites[5] = {16, 16, clip_width, clip_height};  // tail right
  snake_sprites[6] = {32, 16, clip_width, clip_height};  // tail down
  snake_sprites[7] = {48, 16, clip_width, clip_height};  // tail left

  snake_sprites[8] = {0, 32, clip_width, clip_height};    // angle-right up
  snake_sprites[9] = {16, 32, clip_width, clip_height};   // tail right
  snake_sprites[10] = {32, 32, clip_width, clip_height};  // tail down
  snake_sprites[11] = {48, 32, clip_width, clip_height};  // top left

  snake_sprites[12] = {0, 48, clip_width, clip_height};   // body vertical
  snake_sprites[13] = {16, 48, clip_width, clip_height};  // body horizontal

  snake_sprites[14] = {32, 48, clip_width, clip_height};  // bunny sprites
}

void Renderer::RenderSnake(Snake const &snake) {
  // Render snake's head
  SDL_Point head = {static_cast<int>(snake.head_x),
                    static_cast<int>(snake.head_y)};
  render_block.x = static_cast<int>(snake.head_x) * render_block.w;
  render_block.y = static_cast<int>(snake.head_y) * render_block.h;
  switch (snake.direction) {
    case Snake::Direction::kUp:
      spritesTex->Render(sdl_renderer, &snake_sprites[0], &render_block);
      break;
    case Snake::Direction::kDown:
      spritesTex->Render(sdl_renderer, &snake_sprites[2], &render_block);
      break;
    case Snake::Direction::kLeft:
      spritesTex->Render(sdl_renderer, &snake_sprites[3], &render_block);
      break;
    case Snake::Direction::kRight:
      spritesTex->Render(sdl_renderer, &snake_sprites[1], &render_block);
      break;
  }

  // Render snake's body
  SDL_Rect bodySprite;
  SDL_Point prev, next, curr;
  for (size_t i = 0; i < snake.body.size(); i++) {
    curr = snake.body[i];

    // snake's tail
    if (i == 0) {
      if (head.y < curr.y) {
        // Up
        bodySprite = snake_sprites[4];
      } else if (head.x > curr.x) {
        // Right
        bodySprite = snake_sprites[5];
      } else if (head.y > curr.y) {
        // Down
        bodySprite = snake_sprites[6];
      } else if (head.x < curr.x) {
        // Left
        bodySprite = snake_sprites[7];
      }
    } else {
      prev = snake.body[i - 1];
      next = snake.body[i + 1];

      if (prev.x < curr.x && next.x > curr.x ||
          next.x < curr.x && prev.x > curr.x) {
        // Horizontal Left-Right
        bodySprite = snake_sprites[13];
      } else if (prev.x < curr.x && next.y > curr.y ||
                 next.x < curr.x && next.y > curr.y) {
        // Angle Left-Down
        bodySprite = snake_sprites[10];
      } else if (prev.y < curr.y && next.y > curr.y ||
                 next.y < curr.y && prev.y > curr.y) {
        // Vertical Up-Down
        bodySprite = snake_sprites[12];
      } else if (prev.y < curr.y && next.x < curr.x ||
                 next.y < curr.y && prev.x < curr.x) {
        // Angle Top-Left
        bodySprite = snake_sprites[11];
      } else if (prev.x > curr.x && next.y < curr.y ||
                 next.x > curr.x && prev.y < curr.y) {
        // Angle Right-Up
        bodySprite = snake_sprites[8];
      } else if (prev.y > curr.y && next.x > curr.x ||
                 next.y > curr.y && prev.x > curr.x) {
        // Angle Down-Right
        bodySprite = snake_sprites[9];
      }
    }

    render_block.x = snake.body[i].x * render_block.w;
    render_block.y = snake.body[i].y * render_block.h;
    spritesTex->Render(sdl_renderer, &bodySprite, &render_block);
  }
}

void Renderer::RenderBunny(SDL_Point const &bunny) {
  render_block.x = bunny.x * render_block.w;
  render_block.y = bunny.y * render_block.h;
  spritesTex->Render(sdl_renderer, &snake_sprites[14], &render_block);
}

void Renderer::RenderRoad() {
  SDL_Rect fitWidth;
  fitWidth.x = 0;
  fitWidth.w = screen_width;
  fitWidth.h = jpgTex->GetHeight();

  fitWidth.y = screen_height / 4;
  jpgTex->Render(sdl_renderer, &fitWidth);
  fitWidth.y = screen_height / 2;
  jpgTex->Render(sdl_renderer, &fitWidth);
}

void Renderer::Render(Snake const &snake, SDL_Point const &bunny) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render road
  RenderRoad();

  // Render food
  RenderBunny(bunny);

  // Render snake
  RenderSnake(snake);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
