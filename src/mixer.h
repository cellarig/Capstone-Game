#ifndef MIXER_H_
#define MIXER_H_

#include "SDL_mixer.h"

class Mixer {
 public:
  Mixer();
  ~Mixer();

  bool LoadSoundEffects();
  void PlayEatingSound();

 private:
  Mix_Chunk* mSnakeEating;
};

#endif /* MIXER_H_ */
