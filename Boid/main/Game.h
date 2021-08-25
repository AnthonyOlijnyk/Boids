#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Flock.h"
#include "Boid.h"
#include "ObstacleCollection.h"

class Game
{

private:
	std::vector<std::string> paths;
	std::vector<SDL_Texture*> textures;
	bool isRunning = true;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* window = NULL;
	SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* boidTexture = NULL;
	Flock flock;
	ObstacleCollection obstacles;
	int boidPopulation = 50;
	size_t numberOfObstacles = 0;
	int obstacleWidth = 10;
	int obstacleHeight = 10;
	float start = 0.f;
	float end = 0.f;
	float deltaTime = 0.f;

public:
	Game();
	void run();
	void initRenderer();
	void initWindow();
	void initImage();
	void initPaths();
	void initFlock();
	void initObstacles();
	void addObstacleOnClick();
	void addBoidOnClick();
	void setWindowIcon();
	SDL_Texture* loadTexture(const char* path);
	float getTimeSeconds();
	void clearMemory();
	void quit();
};

