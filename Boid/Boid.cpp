#include "Boid.h"
#include "math.h"
#include "Utils.h"

Boid::Boid(float xPosition, float yPosition, float xVelocity, float yVelocity, double angle, SDL_Texture* boidTexture)
	: xPosition(xPosition), yPosition(yPosition), xVelocity(xVelocity), yVelocity(yVelocity), 
	  angle(angle), boidTexture(boidTexture)
{
}



void Boid::update(float deltaTime, int screenWidth, int screenHeight, std::vector<Boid> boids, SDL_Renderer* renderer)
{
	this->getCloseBoids(boids);
	this->align();
	this->applyImpulse(deltaTime);
	this->checkBounds(screenWidth, screenHeight);
	this->closeBoids.clear();
	this->renderBoid(renderer);
}

void Boid::renderBoid(SDL_Renderer* renderer)
{
	SDL_Rect position = { (int)this->xPosition, (int)this->yPosition, this->width, this->height };
	SDL_RenderCopyEx(renderer, this->boidTexture, NULL, &position, this->angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
}

void Boid::checkBounds(int width, int height)
{
	if (this->xPosition > width)
	{
		this->xPosition = 0;
	}
	else if (this->xPosition < 0)
	{
		this->xPosition = (float) width;
	}

	if (this->yPosition > height)
	{
		this->yPosition = 0;
	}
	else if (this->yPosition < 0)
	{
		this->yPosition = (float) height;
	}

}

void Boid::generateRandomImpulse()
{
	this->xAcceleration = (float) ((rand() % 2) - 1);
	this->yAcceleration = (float) ((rand() % 2) - 1);
}

void Boid::applyImpulse(float deltaTime)
{
	this->updateVelocity(deltaTime);
	this->limitVelocity();
	this->updatePosition(deltaTime);
}

void Boid::updateVelocity(float deltaTime)
{
	this->xVelocity += this->xAcceleration * this->friction * deltaTime;
	this->yVelocity += this->yAcceleration * this->friction * deltaTime;
}

void Boid::limitVelocity()
{
	if (std::abs(this->xVelocity) > maxSpeed)
	{
		this->xVelocity = maxSpeed;
	}
	if (std::abs(this->yVelocity) > maxSpeed)
	{
		this->yVelocity = maxSpeed;
	}
	this->angle = Utils::findAngleRadians(this->yVelocity, this->xVelocity);
}

void Boid::updatePosition(float deltaTime)
{
	this->xPosition += this->xVelocity * deltaTime;
	this->yPosition += this->yVelocity * deltaTime;
}

void Boid::getCloseBoids(std::vector<Boid> &boids)
{
	for (int i = 0; i < boids.size(); i++)
	{
		float distance = Utils::distance(this->xPosition, this->yPosition, boids[i].getXPosition(), boids[i].getYPosition());
		if (distance != 0 && distance < distanceConsideredClose)
		{
			this->closeBoids.push_back(boids[i]);
		}
	}
}

void Boid::align()
{
	if (closeBoids.size() == 0)
	{
		this->generateRandomImpulse();
		return;
	}
	float totalXVelocity = 0.f;
	float totalYVelocity = 0.f;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		totalXVelocity += closeBoids[i].getXVelocity();
		totalYVelocity += closeBoids[i].getYVelocity();
	}
	float averageXVelocity = totalXVelocity / closeBoids.size();
	float averageYVelocity = totalYVelocity / closeBoids.size();

	this->xAcceleration = averageXVelocity - this->xVelocity;
	this->yAcceleration = averageYVelocity - this->yVelocity;
}

float Boid::getXPosition()
{
	return this->xPosition;
}

float Boid::getYPosition()
{
	return this->yPosition;
}

float Boid::getXVelocity()
{
	return this->xVelocity;
}

float Boid::getYVelocity()
{
	return this->yVelocity;
}

double Boid::getAngle()
{
	return this->angle;
}