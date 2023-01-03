#pragma once
#include <iostream>
#include <SDL.h>
//SDL_LIB
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include<sstream>
#include<string>
#include <ctime>

static const int Screen_height = 800;
static const int Screen_width = 600;
static SDL_Window* window;
static SDL_Renderer* renderer;

class BaseObject
{
protected:
	SDL_Texture* texture;
	SDL_Rect rect;
};

namespace cmfunc
{
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	SDL_Texture* LoadImage(SDL_Renderer* renderer, const char* path);
	SDL_Texture* createMessage(SDL_Renderer* renderer, SDL_Color color, const char* mess, TTF_Font* font);
}