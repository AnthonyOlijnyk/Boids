#include "Flock.h"

Flock::Flock(int numBoids, int width, int height, std::vector<SDL_Texture*> boidTextures)
{
	this->widthBound = width;
	this->heightBound = height;
	for (int i = 0; i < numBoids; i++)
	{
		this->flock.push_back(Boid(width, height, boidTextures[rand() % boidTextures.size()]));
	}
}

Boid* Flock::getBoid(int index)
{
	return &this->flock[index];
}

size_t Flock::getSize()
{
	return this->flock.size();
}

void Flock::simulate(float deltaTime, SDL_Renderer* renderer)
{
	for (int i = 0; i < this->getSize(); i++)
	{
		this->getBoid(i)->update(deltaTime, this->widthBound, this->heightBound, this->flock, renderer);
	}
}
