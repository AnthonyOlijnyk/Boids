#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	this->initPaths();
	this->initImage();
	this->initWindow();
	this->initRenderer();
	for (std::string path : paths)
	{
		SDL_Texture* texture = this->loadTexture(path.c_str());
		this->textures.push_back(texture);
	}
	this->initFlock();
	this->initObstacles();
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
	this->setWindowIcon();
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
		printf("IMG_Init: Failed to init required png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		this->isRunning = false;
	}
}

void Game::initPaths()
{
	for (size_t i = 1; i <= 56; ++i)
	{
		std::string path = "gfx/" + std::to_string(i) + ".png";
		this->paths.push_back(path);
	}
}

void Game::run()
{
	while (this->isRunning)
	{
		this->start = this->getTimeSeconds();
		SDL_SetRenderDrawColor(this->renderer, 45, 45, 45, 255);
		SDL_RenderClear(this->renderer);
		while (SDL_PollEvent(&this->event))
		{
			switch (this->event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_o:
							this->addObstacleOnClick();
							break;

						case SDLK_b:
							this->addBoidOnClick();
							break;

						case SDLK_p:
							this->obstacles.clearObstacles();
							break;

						case SDLK_n:
							this->flock.clearFlock();
							break;

						case SDLK_r:
							this->flock.clearFlock();
							this->obstacles.clearObstacles();
							break;

						case SDLK_i:
							this->obstacles.removeLast();
							break;

						case SDLK_v:
							this->flock.removeLast();


						default:
							break;
					}
					break;

				case SDL_QUIT:
					this->isRunning = false;
					break;

				default:
					break;
			}
		}
		SDL_Delay(10);
		this->end = this->getTimeSeconds();
		this->deltaTime = this->end - this->start;
		std::vector<Obstacle> obstaclesInCollection = this->obstacles.getObstacleCollection();
		this->flock.simulate(this->deltaTime, obstaclesInCollection, this->renderer);
		this->obstacles.renderObstacles(this->renderer);
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

void Game::initFlock()
{
	this->flock = Flock(this->boidPopulation, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, this->textures);
}

void Game::initObstacles()
{
	this->obstacles = ObstacleCollection(this->numberOfObstacles, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, this->obstacleWidth, this->obstacleHeight);
}

void Game::addObstacleOnClick()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	this->obstacles.addObstacle(mouseX, mouseY, this->obstacleWidth, this->obstacleHeight);
}

void Game::addBoidOnClick()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	this->flock.addBoid((double)mouseX, (double)mouseY);
}

void Game::setWindowIcon()
{
	SDL_Surface* surface = IMG_Load(this->paths[rand() % paths.size()].c_str());
	SDL_SetWindowIcon(this->window, surface);
	SDL_FreeSurface(surface);
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