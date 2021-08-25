#include "Flock.h"

Flock::Flock(int numBoids, int width, int height, std::vector<SDL_Texture*> boidTextures)
	: widthBound(width), heightBound(height), boidTextures(boidTextures)
{
	for (int i = 0; i < numBoids; i++)
	{
		this->flock.push_back(Boid(width, height, this->boidTextures[rand() % this->boidTextures.size()]));
	}
}

Flock::Flock()
{
	this->heightBound = 0;
	this->widthBound = 0;
}

Boid* Flock::getBoid(int index)
{
	return &this->flock[index];
}

size_t Flock::getSize()
{
	return this->flock.size();
}

void Flock::simulate(float deltaTime, std::vector<Obstacle>& obstacles, SDL_Renderer* renderer)
{
	for (int i = 0; i < this->getSize(); i++)
	{
		this->getBoid(i)->update(deltaTime, this->widthBound, this->heightBound, this->flock, obstacles, renderer);
	}
}

void Flock::addBoid(double x, double y)
{
	flock.push_back(Boid(x, y, this->boidTextures[rand() % this->boidTextures.size()]));
}

void Flock::clearFlock()
{
	this->flock.clear();
}

void Flock::removeLast()
{
	if (this->flock.empty())
	{
		return;
	}

	this->flock.pop_back();
}
