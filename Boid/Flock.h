#pragma once
#include <vector>
#include <time.h>
#include "Boid.h"
#include "MathAndPhysics.h"

class Flock
{
private:
	std::vector<Boid> flock;
	int widthBound;
	int heightBound;

public:
	Flock(int numBoids, const int width, const int height, SDL_Texture* boidTexture);
	Boid* getBoid(int index);
	size_t getSize();
	void simulate(float deltaTime, SDL_Renderer* renderer);
};

