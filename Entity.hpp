#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
	Entity(float p_x, float p_y, int width, int height, SDL_Texture* p_tex);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	int w, h;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};