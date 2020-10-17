#ifndef SOUNDMAKER_H_
#define SOUNDMAKER_H_

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

#endif /* SOUNDMAKER_H_ */
