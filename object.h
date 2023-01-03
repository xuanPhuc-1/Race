#pragma once
#include "cmfunc.h"

class Car : public BaseObject
{
public:
	void init(SDL_Renderer* renderer, const char* s, int i);
	void move_left(int i);
	void move_right(int i);
	void render(SDL_Renderer* renderer);
	SDL_Rect getRect()
	{
		return rect;
	}
};

class Button : public BaseObject
{
public:
	void init(SDL_Renderer* renderer, const char* s, int i);

	void render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
};

class Obstacle : public BaseObject
{
public:
	bool status;
	void init(SDL_Renderer* renderer, const char* s);
	void create(int i);
	bool move(SDL_Renderer* renderer)
	{
		rect.y += 5;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		if (rect.y >= Screen_height) return false;
		else return true;
	}
	SDL_Rect getRect()
	{
		return rect;
	}
	void reset()
	{
		rect.y = Screen_height;
	}
};