#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(float p_x, float p_y,int width,int height, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex), w(width), h(height)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = w;
	currentFrame.h = h;
}

float Entity::getX()
{
	return x;
}
float Entity::getY()
{
	return y;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}