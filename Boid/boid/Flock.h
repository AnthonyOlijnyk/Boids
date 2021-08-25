#pragma once
#include <vector>
#include <time.h>
#include "Boid.h"
#include "MathAndPhysics.h"

class Flock
{
private:
	std::vector<Boid> flock;
	std::vector<SDL_Texture*> boidTextures;
	int widthBound;
	int heightBound;

public:
	Flock();
	Flock(int numBoids, const int width, const int height, std::vector<SDL_Texture*> boidTextures);
	Boid* getBoid(int index);
	size_t getSize();
	void simulate(float deltaTime, std::vector<Obstacle>& obstacles, SDL_Renderer* renderer);
	void addBoid(double x, double y);
	void clearFlock();
	void removeLast();
};

