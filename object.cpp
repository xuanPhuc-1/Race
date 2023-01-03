//FUNCTIONS IN CLASS
#include "object.h"
void Car::init(SDL_Renderer* renderer, const char* s, int i)
{
	rect.w = 60;
	rect.h = 95;
	rect.y = 650;
	if (i == 1)
	{
		rect.x = 220;
	}
	if (i == 2)
	{
		rect.x = 410;
	}
	texture = cmfunc::LoadImage(renderer, s);
}

void Button::init(SDL_Renderer* renderer, const char* s, int i)
{

	if (i == 1)
	{
		rect.x = 80;
		rect.y = 100;
		rect.w = 450;
		rect.h = 500;
	}
	if (i == 2)
	{
		rect.x = 80;
		rect.y = 200;
		rect.w = 450;
		rect.h = 500;
	}
	if (i == 3)
	{
		rect.x = 50;
		rect.y = 280;
		rect.w = 450;
		rect.h = 500;
	}
	if (i == 4)
	{
		rect.x = 80;
		rect.y = 380;
		rect.w = 450;
		rect.h = 500;
	}
	texture = cmfunc::LoadImage(renderer, s);
}

void Car::move_left(int i)
{
	if (i == 1)
	{
		if (rect.x - 90 >= 100) rect.x -= 90;
	}
	else
	{
		if (rect.x - 90 >= 320) rect.x -= 90;
	}
}

void Car::move_right(int i)
{
	if (i == 1)
	{
		if (rect.x + 90 <= 300) rect.x += 90;
	}
	else
	{
		if (rect.x + 90 <= 450) rect.x += 90;
	}
}

void Car::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Obstacle::init(SDL_Renderer* renderer, const char* s)
{
	texture = cmfunc::LoadImage(renderer, s);
	rect.w = 80;
	rect.h = 80;
	status = false;
}

void Obstacle::create(int i)
{
	rect.y = -rect.h;
	if (i == 1) rect.x = 128;
	else if (i == 2) rect.x = 213;
	else if (i == 3) rect.x = 313;
	else if (i == 4) rect.x = 403;
	status = true;
}