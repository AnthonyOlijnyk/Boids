#include "Flock.h"
#include "Utils.h"
Flock::Flock(int numBoids, int width, int height, SDL_Texture* boidTexture)
{
	this->updateBounds(width, height);
	srand(time(NULL));
	for (int i = 0; i < numBoids; i++)
	{
		float randomXPosition = (float) (rand() % width);
		float randomYPosition = (float) (rand() % height);
		float randomXVelocity = (float) ((rand() % 500) - 250);
		float randomYVelocity = (float) ((rand() % 500) - 250);
		double calculatedAngle = Utils::findAngleRadians(randomYVelocity, randomXVelocity);
		std::cout << "Angle" << std::endl;
		std::cout << randomXVelocity << "," << randomYVelocity << std::endl;
		std::cout << calculatedAngle * 180 / M_PI << std::endl;
		this->flock.push_back(
			Boid
			(
				randomXPosition, 
				randomYPosition, 
				randomXVelocity, 
				randomYVelocity, 
				calculatedAngle, 
				boidTexture
			)
		);
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

std::vector<Boid> Flock::getFlock()
{
	return this->flock;
}

void Flock::simulate(float deltaTime, SDL_Renderer* renderer)
{
	for (int i = 0; i < this->getSize(); i++)
	{
		this->getBoid(i)->update(deltaTime, this->widthBound, this->heightBound, this->flock, renderer);
	}
}

void Flock::updateBounds(int width, int height)
{
	this->widthBound = width;
	this->heightBound = height;
}
