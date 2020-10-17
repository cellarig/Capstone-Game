#ifndef SPRITESTEXTURE_H_
#define SPRITESTEXTURE_H_

#include <string>

#include "SDL.h"
#include "SDL_image.h"

class BaseTexture {
 public:
  BaseTexture();
  virtual ~BaseTexture();

  virtual bool LoadFromFile(const std::string& path,
                            SDL_Renderer* renderer) = 0;

 protected:
  void FreeTexture();

  // The actual hardware texture
  SDL_Texture* mTexture;
};

class SpritesTexture : public BaseTexture {
 public:
  SpritesTexture();

  bool LoadFromFile(const std::string& path, SDL_Renderer* renderer) override;
  void Render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* grid);
};

class JpgImageTexture : public BaseTexture {
 public:
  JpgImageTexture();

  bool LoadFromFile(const std::string& path, SDL_Renderer* renderer) override;
  void Render(SDL_Renderer* renderer, SDL_Rect* location);

  int GetWidth() const { return mWidth; }
  int GetHeight() const { return mHeight; }

 private:
  int mWidth;
  int mHeight;
};

#endif /* SPRITESTEXTURE_H_ */