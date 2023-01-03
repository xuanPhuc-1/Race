#include "cmfunc.h"
#include "object.h"
std::string ss, ss2;
const char* s;
const char* s2;


int main(int argc, char* argv[])
{	
	cmfunc::initSDL(window, renderer);

//CREATE TEXTURE
	SDL_Texture* background1 = cmfunc::LoadImage(renderer, "background1.png");
	SDL_Texture* game_over = cmfunc::LoadImage(renderer, "over_game.png");
	SDL_Texture* background = cmfunc::LoadImage(renderer, "background2.png");

//FONT AND COLOR
	TTF_Font* score_font = TTF_OpenFont("fontA.ttf", 150);
	SDL_Color yellow = { 255,255, 0 };

//AUDIO AND MUSIC
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* bgm2 = Mix_LoadMUS("bgm.mp3"); 
	Mix_Music* bgm = Mix_LoadMUS("play.mp3");
	Mix_Chunk* sound = Mix_LoadWAV("over.wav"); 

//CREATE RECT
	SDL_Rect rect_1;
	SDL_Rect rect_2;
	SDL_Rect rect_3;
	SDL_Rect rect_4;

	rect_1.y = 0;
	rect_1.x = 0;
	rect_2.y = -Screen_height;
	rect_2.x = 0;
	rect_1.w = Screen_width;
	rect_1.h = Screen_height;
	rect_2.w = Screen_width;
	rect_2.h = Screen_height;
	
	rect_3.y = 30;
	rect_3.x = 30;
	rect_3.h = 100;
	rect_3.w = 100;

	rect_4.y = 20;
	rect_4.x = 250;
	rect_4.h = 100;
	rect_4.w = 100;

// INIT SCORE
	int score = 0;
	int total_score = 0;

	SDL_Event event;
	int mouse_x, mouse_y;
	
//INIT PLAYER'S CAR
	Car car[2];
	car[0].init(renderer,"car1.png", 1);
	car[1].init(renderer,"car4.png", 2);

//INIT BUTTON
	Button button[4];
	button[0].init(renderer, "start.png",1);
	button[1].init(renderer, "exit.png",2);
	button[2].init(renderer, "playagain.png", 3);
	button[3].init(renderer, "exit.png", 4);

//INIT OBSTACLE
	Obstacle obs[10];	
	for (int i = 0; i < 10; i++) obs[i].init(renderer, "vatcan66.png");

	int r1, r2, cd1 = 0, cd2 = 0;
	int x, y;

//THE FIRST 
start:
	Mix_PlayMusic(bgm2, 10); 
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
//START AND EXIT BUTTON
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (mouse_x >= 200 && mouse_x <= 410 && mouse_y >= 242 && mouse_y <= 295) goto play;
				if (mouse_x >= 200 && mouse_x <= 410 && mouse_y >= 342 && mouse_y <= 395) return 0;
			}
			if (event.type == SDL_QUIT) return 1;
		}

//RENDER BACKGROUND AND BUTTON
		SDL_RenderCopy(renderer, background1, NULL, NULL);
		button[0].render(renderer);
		button[1].render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}


play:
	Mix_PlayMusic(bgm, 10);
	score = 0;
	for (int i = 0; i < 10; i++) obs[i].reset();

	while (true)
	{
		while (SDL_PollEvent(&event))
		{

//MOVEMENT OF THE CAR
			if (event.type == SDL_QUIT) return 1;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_a) car[0].move_left(1);
				if (event.key.keysym.sym == SDLK_LEFT) car[1].move_left(2);
				if (event.key.keysym.sym == SDLK_d) car[0].move_right(1);
				if (event.key.keysym.sym == SDLK_RIGHT) car[1].move_right(2);
			}
		}


//RUNING SCREEN
		rect_1.y++;
		rect_2.y++;
		if (rect_1.y == Screen_height)
		{
			rect_1.y = 0;
			rect_2.y = -Screen_height;
		}

//INIT OBSTACLE
		if (cd1 == 0)
		{			
			srand(time(NULL));
			r1 = rand() % 4 + 1;
			if (r1 == 1 || r1 == 2)
			{
				for (int i = 0; i < 5; i++)
					if (obs[i].status == false)
					{
						
						obs[i].create(r1);
						cd1 = 60;
						break;
					}
			}						
		}
		else cd1--;
		

		if (cd2 == 0)
		{
			
			r2 = rand() % 4 + 1;
			if (r2 == 3 || r2 == 4)
			{
				for (int i = 5; i < 10; i++)
					if (obs[i].status == false)
					{
						obs[i].create(r2);
						cd2 = 60;
						break;
					}
			}			
		}
		else cd2--;

//collision condition
		for (int i = 0;i < 5;i++)
			if (car[0].getRect().x >= obs[i].getRect().x && car[0].getRect().x <= obs[i].getRect().x + obs[i].getRect().w || car[0].getRect().x + car[0].getRect().w >= obs[i].getRect().x && car[0].getRect().x + car[0].getRect().w <= obs[i].getRect().x + obs[i].getRect().w)
				if (car[0].getRect().y >= obs[i].getRect().y && car[0].getRect().y <= obs[i].getRect().y + obs[i].getRect().h || car[0].getRect().y + car[0].getRect().h >= obs[i].getRect().y && car[0].getRect().y + car[0].getRect().h <= obs[i].getRect().y + obs[i].getRect().h)
				{
					Mix_PlayChannel(-1, sound, 0);
					Mix_PauseMusic();
					goto lose;
					
				}

		for (int i = 5; i < 10; i++)
			if (car[1].getRect().x >= obs[i].getRect().x && car[1].getRect().x <= obs[i].getRect().x + obs[i].getRect().w || car[1].getRect().x + car[1].getRect().w >= obs[i].getRect().x && car[1].getRect().x + car[1].getRect().w <= obs[i].getRect().x + obs[i].getRect().w)
				if (car[1].getRect().y >= obs[i].getRect().y && car[1].getRect().y <= obs[i].getRect().y + obs[i].getRect().h || car[1].getRect().y + car[1].getRect().h >= obs[i].getRect().y && car[1].getRect().y + car[1].getRect().h <= obs[i].getRect().y + obs[i].getRect().h)
				{
					Mix_PlayChannel(-1, sound, 0);
					Mix_PauseMusic();
					goto lose;
				}

//RENDER RUNING BACKGROUND
		SDL_RenderCopy(renderer, background, NULL, &rect_1);
		SDL_RenderCopy(renderer, background, NULL, &rect_2);

//CONVERT DATA FROM INT TO STRING AND FROM STRING TO CHAR		
		ss = std::to_string(score);
		s = ss.c_str();
		SDL_Texture* t1 = cmfunc::createMessage(renderer, yellow, s, score_font);
		
		score += 1;
		total_score += score;

//RENDER CAR
		SDL_RenderCopy(renderer, t1, NULL, &rect_3);
		for (int i = 0; i < 2; i++) car[i].render(renderer);

//RENDER OBSTACEL
		for (int i = 0; i < 10; i++)
			if (obs[i].status == true) obs[i].status = obs[i].move(renderer);

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
lose:
	total_score = 0;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{

//RENDER BACKGROUND AND PLAY AGAIN BUTTON
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (mouse_x >= 170 && mouse_x <= 430 && mouse_y >= 410 && mouse_y <= 470)				
					goto play;				
				if (mouse_x >= 200 && mouse_x <= 400 && mouse_y >= 520 && mouse_y <= 570) return 0;
			}
			if (event.type == SDL_QUIT) return 1;
		}

		SDL_Texture* t2 = cmfunc::createMessage(renderer, yellow, s, score_font);

//RENDER BACKGROUND AND PLAY AGAIN BUTTON
		SDL_RenderCopy(renderer, game_over, NULL, NULL);
		button[2].render(renderer);
		button[3].render(renderer);
		SDL_RenderCopy(renderer, t2, NULL, &rect_4);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return 0;
}