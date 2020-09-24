#include "spritestexture.h"

#include <iostream>

SpritesTexture::SpritesTexture() : mTexture(nullptr) {}

SpritesTexture::~SpritesTexture() { free(); }

void SpritesTexture::free() {
  // Free texture if it exists
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

void SpritesTexture::render(SDL_Renderer* renderer, SDL_Rect* clip,
                            SDL_Rect* grid) {
  // Render to screen
  SDL_RenderCopy(renderer, mTexture, clip, grid);
}

bool SpritesTexture::loadFromFile(std::string path, SDL_Renderer* renderer) {
  // Get rid of preexisting texture
  free();

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
  return mTexture != NULL;
}