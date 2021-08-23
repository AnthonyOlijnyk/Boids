#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Flock.h"
#include "Boid.h"

class Game
{
public:
	Game();
	void run();
	void initRenderer();
	void initWindow();
	void initImage();
	SDL_Texture* loadTexture(const char* path);
	float getTimeSeconds();
	void clearMemory();
	void quit();

private:
	bool isRunning = true;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* window = NULL;
	SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* boidTexture = NULL;
};

