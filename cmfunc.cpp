#include "cmfunc.h"
void cmfunc::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	window = SDL_CreateWindow("Race", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_width, Screen_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, Screen_width, Screen_height);
	TTF_Init();
}

SDL_Texture* cmfunc :: LoadImage(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}

SDL_Texture* cmfunc::createMessage(SDL_Renderer* renderer, SDL_Color color, const char* mess, TTF_Font* font)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, mess, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}
