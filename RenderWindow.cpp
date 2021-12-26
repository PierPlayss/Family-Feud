#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;



RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

//Text::Text(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color) {
//	text_texture = RenderWindow::loadFont(cfont_path, int font_size, const std::string &message_text, const SDL_Color &color)
//}
//
//void Text::displaytext() const {
//
//}
//
//SDL_Texture* RenderWindow::loadFont(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color) {
//	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
//	if (!font) {
//		cout << "Failed to load font" << endl;
//	}
//	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
//	if (!text_surface) {
//		cout << "Failed to render text surface" << endl;
//	}
//
//	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
//	if (!text_surface) {
//		cout << "Failed to render text texture" << endl;
//	}
//	SDL_FreeSurface(text_surface);
//	return text_texture;
//}
void RenderWindow::drawText(const char* msg, int x, int y, int r, int g, int b, int size) {
	SDL_Surface* surf;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("res/fonts/DezenPro.ttf", size);
	
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	rect.x = x;
	rect.y = y;
	rect.w = surf -> w  ;
	rect.h = surf -> h  ;
	TTF_CloseFont(font); 
	//IMG_SavePNG(surf, "image.png");
	//SDL_SaveBMP(surf, "image.bmp");
	SDL_FreeSurface(surf);
	
	

	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_DestroyTexture(texture);

}

//SDL_Texture* RenderWindow::Points(const char* msg, int x, int y, int r, int g, int b, int size,int &w,int &h) {
//	SDL_Surface* surf;
//	SDL_Texture* texture;
//	TTF_Font* font = TTF_OpenFont("res/fonts/Warownia.otf", size);
//
//	SDL_Color color;
//	color.r = r;
//	color.g = g;
//	color.b = b;
//	color.a = 255;
//	SDL_Rect rect;
//	surf = TTF_RenderText_Solid(font, msg, color);
//	texture = SDL_CreateTextureFromSurface(renderer, surf);
//	rect.x = x;
//	rect.y = y;
//	rect.w = surf->w;
//	rect.h = surf->h;
//	TTF_CloseFont(font);
//	IMG_SavePNG(surf,"res / gfx / image.png");
//	SDL_FreeSurface(surf);
//
//	
//
//	return texture;
//}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, double angle, float multiplicador) {

	SDL_Point pt;
	pt.x = p_entity.getCurrentFrame().x;
	pt.y = p_entity.getCurrentFrame().y;

	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h * multiplicador;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst,angle,&pt, SDL_FLIP_NONE);
}

void RenderWindow::render(Entity& p_entity, float multiplicador)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h *multiplicador;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::render(Entity& p_entity, SDL_Rect &rect)
{
	SDL_Rect src;
	src.x = rect.x;
	src.y = rect.y;
	src.w = rect.w;
	src.h = rect.h;

	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h/4;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::animation(Entity& p_entity,SDL_Rect &rect, SDL_Rect& pos) {
	
	SDL_Rect dst;
	dst.x = rect.x;
	dst.y = rect.y;
	dst.w = rect.w;
	dst.h = rect.h;

	SDL_Rect final;
	final.x = pos.x;
	final.y = pos.y;
	final.w = pos.w;
	final.h = pos.h;


	SDL_RenderCopy(renderer, p_entity.getTex(), &dst, &final);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
