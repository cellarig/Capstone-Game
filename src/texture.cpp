#include "texture.h"

#include <iostream>

BaseTexture::BaseTexture() : mTexture(nullptr) {}

BaseTexture::~BaseTexture() { FreeTexture(); }

void BaseTexture::FreeTexture() {
  // Free texture if it exists
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

SpritesTexture::SpritesTexture() : BaseTexture() {}

bool SpritesTexture::LoadFromFile(const std::string& path,
                                  SDL_Renderer* renderer) {
  // Get rid of preexisting texture
  FreeTexture();

  // The final texture
  SDL_Texture* newTexture = nullptr;

  // Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    std::cerr << "Unable to load image " << path
              << "! SDL_image Error: " << IMG_GetError() << "\n";
  } else {
    // Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 255, 255));

    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      std::cerr << "Unable to create texture " << path
                << "! SDL_image Error: " << IMG_GetError() << "\n";
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // Return success
  mTexture = newTexture;
  return mTexture != nullptr;
}

void SpritesTexture::Render(SDL_Renderer* renderer, SDL_Rect* clip,
                            SDL_Rect* grid) {
  // Render to screen
  SDL_RenderCopy(renderer, mTexture, clip, grid);
}

JpgImageTexture::JpgImageTexture() : BaseTexture(), mWidth(0), mHeight(0) {}

bool JpgImageTexture::LoadFromFile(const std::string& path,
                                   SDL_Renderer* renderer) {
  // Get rid of preexisting texture
  FreeTexture();
  mWidth = 0;
  mHeight = 0;

  SDL_Texture* newTexture = nullptr;

  // Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    std::cerr << "Unable to load image " << path
              << "! SDL_Error: " << SDL_GetError() << "\n";
  } else {
    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      std::cerr << "Unable to create texture from " << path
                << "! SDL_Error: " << SDL_GetError() << "\n";
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // Return success
  mTexture = newTexture;
  return mTexture != nullptr;
}

void JpgImageTexture::Render(SDL_Renderer* renderer, SDL_Rect* location) {
  // Render to screen
  SDL_RenderCopy(renderer, mTexture, nullptr, location);
}