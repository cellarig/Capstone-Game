#include "mixer.h"

#include <iostream>

Mixer::Mixer() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: "
              << Mix_GetError() << "\n";
  }
}

Mixer::~Mixer() { Mix_FreeChunk(mSnakeEating); }

bool Mixer::LoadSoundEffects() {
  bool success = true;
  mSnakeEating = Mix_LoadWAV("../res/eatingSound.wav");
  if (mSnakeEating == nullptr) {
    std::cerr << "Failed to load sound effect! SDL_mixer Error: "
              << Mix_GetError() << "\n";
    success = false;
  }
  return success;
}

void Mixer::PlayEatingSound() {
  if (mSnakeEating != nullptr) Mix_PlayChannel(-1, mSnakeEating, 0);
}