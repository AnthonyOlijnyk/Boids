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
	const std::vector<const char*> paths = {
		"gfx/white.png",
		"gfx/dark_blue.png",
		"gfx/green.png",
		"gfx/light_blue.png",
		"gfx/light_purple.png",
		"gfx/light_red.png",
		"gfx/navy_blue.png",
		"gfx/orange.png",
		"gfx/pink.png",
		"gfx/purple.png",
		"gfx/red.png",
		"gfx/turk.png",
		"gfx/yellow.png"
	};
	std::vector<SDL_Texture*> textures;
	bool isRunning = true;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* window = NULL;
	SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* boidTexture = NULL;
};

