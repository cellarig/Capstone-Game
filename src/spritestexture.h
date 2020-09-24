#ifndef SPRITESTEXTURE_H_
#define SPRITESTEXTURE_H_

#include <string>

#include "SDL.h"
#include "SDL_image.h"

class SpritesTexture {
 public:
  SpritesTexture();
  ~SpritesTexture();

  bool loadFromFile(std::string path, SDL_Renderer* renderer);
  void free();
  void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* grid);

 private:
  // The actual hardware texture
  SDL_Texture* mTexture;
};

#endif /* SPRITESTEXTURE_H_ */