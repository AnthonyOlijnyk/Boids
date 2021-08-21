#include "Game.h"
#include "Boid.h"
#include <iostream>

Game::Game()
{
	this->initWindow();
	this->initRenderer();
	this->initImage();
	this->boidTexture = loadTexture("boid.png");
}

void Game::initWindow()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		this->isRunning = false;
	}
	else
	{
		this->window = SDL_CreateWindow("Boids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			this->isRunning = false;
		}
	}
}

void Game::initRenderer()
{
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::initImage()
{
	int flag = IMG_INIT_PNG;
	int initted = IMG_Init(flag);
	if ((initted & flag) != flag) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		this->isRunning = false;
	}
}

void Game::run()
{
	float start = 0;
	float end = 0;
	float deltaTime = 0;
	Flock flock(5, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, this->boidTexture);
	while (this->isRunning)
	{
		start = this->getTimeSeconds();
		SDL_RenderClear(this->renderer);
		while (SDL_PollEvent(&this->event))
		{
			switch (this->event.type)
			{
			case SDL_QUIT:
				this->isRunning = false;
				break;

			default:
				break;
			}
		}
		SDL_Delay(10);
		end = this->getTimeSeconds();
		deltaTime = end - start;
		flock.simulate(deltaTime, this->renderer);
		SDL_RenderPresent(this->renderer);
	}
	this->clearMemory();
	this->quit();
}

SDL_Texture* Game::loadTexture(const char* path)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);

	if (texture == NULL)
	{
		printf("Failed to load texture. Error: %s", SDL_GetError());
		this->isRunning = false;
	}

	return texture;
}

float Game::getTimeSeconds()
{
	float t = SDL_GetTicks();
	return t / 1000;
}

void Game::clearMemory()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void Game::quit()
{
	SDL_Quit();
}