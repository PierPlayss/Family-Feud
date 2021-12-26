#pragma once
#include <SDL2/SDL_mixer.h>
#include <vector>
class SDL2SoundEffects
{
public:
  SDL2SoundEffects();
  ~SDL2SoundEffects();

  void addSoundEffect(const char* path);

  void playSoundEffect(const int which) const;

private:
  
  std::vector<Mix_Chunk*> mSoundEffectBank;

};
