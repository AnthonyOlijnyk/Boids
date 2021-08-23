#include "Boid.h"

Boid::Boid(int screenWidth, int screenHeight, SDL_Texture* boidTexture) : boidTexture(boidTexture)
{
	this->position = MathAndPhysics::randomPositionVector(screenWidth, screenHeight);
	this->velocity = MathAndPhysics::randomVector(this->maxSpeed);
	this->acceleration = MathAndPhysics::randomVector(this->maxAcceleration);
}

void Boid::update(float deltaTime, int screenWidth, int screenHeight, std::vector<Boid> boids, SDL_Renderer* renderer)
{
	this->getCloseBoids(boids);
	this->calculateFNet();
	this->applyImpulse(deltaTime, screenWidth, screenHeight);
	this->closeBoids.clear();
	this->renderBoid(renderer);
}

void Boid::renderBoid(SDL_Renderer* renderer)
{
	SDL_Rect position = { (int)this->position.x, (int)this->position.y, this->width, this->height };
	SDL_RenderCopyEx(renderer, this->boidTexture, NULL, &position, this->velocity.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
}

void Boid::checkBounds(int width, int height)
{
	if (this->position.x > width)
	{
		this->position.x = 0.f;
	}
	else if (this->position.x < 0)
	{
		this->position.x = (double) width;
	}

	if (this->position.y > height)
	{
		this->position.y = 0.f;
	}
	else if (this->position.y < 0)
	{
		this->position.y = (double) height;
	}

}

void Boid::applyImpulse(float deltaTime, int screenWidth, int screenHeight)
{
	this->updateVelocity(deltaTime);
	this->limitVelocity();
	this->updatePosition(deltaTime);
	this->checkBounds(screenWidth, screenHeight);
}

void Boid::updateVelocity(float deltaTime)
{
	MathAndPhysics::Vector correctedAcceleration = MathAndPhysics::multiplyScalar(this->acceleration, this->friction * deltaTime);
	this->velocity = MathAndPhysics::addVectors(this->velocity, correctedAcceleration);
}

void Boid::limitVelocity()
{
	if (this->velocity.x > this->maxSpeed)
	{
		this->velocity.x = this->maxSpeed;
	}
	else if (this->velocity.x < -this->maxSpeed)
	{
		this->velocity.x = -this->maxSpeed;
	}
	if (this->velocity.y > this->maxSpeed)
	{
		this->velocity.y = this->maxSpeed;
	}
	else if (this->velocity.y < -this->maxSpeed)
	{
		this->velocity.y = -this->maxSpeed;
	}
	this->velocity.angle = MathAndPhysics::findAngleRadians(this->velocity.y, this->velocity.x);
}

void Boid::updatePosition(float deltaTime)
{
	MathAndPhysics::Vector correctedVelocity = MathAndPhysics::multiplyScalar(this->velocity, deltaTime);
	this->position = MathAndPhysics::addVectors(this->position, this->velocity);
}

void Boid::getCloseBoids(std::vector<Boid> &boids)
{
	for (int i = 0; i < boids.size(); i++)
	{
		MathAndPhysics::Vector candidateBoidPosition = boids[i].getPosition();
		double distance = MathAndPhysics::distance(this->position.x, this->position.y, candidateBoidPosition.x, candidateBoidPosition.y);
		if (distance != 0 && distance < this->distanceConsideredClose)
		{
			this->closeBoids.push_back(boids[i]);
		}
	}
}

MathAndPhysics::Vector Boid::align()
{
	if (closeBoids.size() == 0)
	{
		return MathAndPhysics::randomVector(this->maxAcceleration);
	}

	MathAndPhysics::Vector totalVelocityVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		MathAndPhysics::Vector closeBoidVelocity = closeBoids[i].getVelocity();
		totalVelocityVector = MathAndPhysics::addVectors(totalVelocityVector, closeBoidVelocity);
	}
	MathAndPhysics::Vector averageVelocity = MathAndPhysics::multiplyScalar(totalVelocityVector, 1.f / closeBoids.size());
	MathAndPhysics::Vector correctedAverage = MathAndPhysics::setMagnitude(averageVelocity, this->maxSpeed);
	MathAndPhysics::Vector correctionForce = MathAndPhysics::subtractVectors(correctedAverage, this->velocity);

	return correctionForce;
}

MathAndPhysics::Vector Boid::cohesion()
{
	if (closeBoids.size() == 0)
	{
		return MathAndPhysics::randomVector(this->maxAcceleration);
	}

	MathAndPhysics::Vector totalPositionVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		MathAndPhysics::Vector closeBoidsPosition = this->closeBoids[i].getPosition();
		totalPositionVector = MathAndPhysics::addVectors(totalPositionVector, closeBoidsPosition);
	}
	MathAndPhysics::Vector averagePosition = MathAndPhysics::multiplyScalar(totalPositionVector, 1.f / this->closeBoids.size());
	MathAndPhysics::Vector correctionDirection = MathAndPhysics::subtractVectors(averagePosition, this->position);
	MathAndPhysics::Vector optimalVelocity = MathAndPhysics::setMagnitude(correctionDirection, this->maxSpeed);
	MathAndPhysics::Vector correctionForce = MathAndPhysics::subtractVectors(optimalVelocity, this->velocity);

	return correctionForce;
}

MathAndPhysics::Vector Boid::separation()
{
	if (closeBoids.size() == 0)
	{
		return MathAndPhysics::randomVector(this->maxAcceleration);
	}

	MathAndPhysics::Vector totalDifferenceVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		MathAndPhysics::Vector closeBoidsPosition = this->closeBoids[i].getPosition();
		double distanceFromSelf = MathAndPhysics::distance(this->position.x, this->position.y, closeBoidsPosition.x, closeBoidsPosition.y);
		MathAndPhysics::Vector differenceVector = MathAndPhysics::subtractVectors(this->position, closeBoidsPosition);
		MathAndPhysics::Vector correctedDifference = MathAndPhysics::multiplyScalar(differenceVector, 1.f / distanceFromSelf);
		totalDifferenceVector = MathAndPhysics::addVectors(totalDifferenceVector, correctedDifference);
	}
	MathAndPhysics::Vector averageDifference = MathAndPhysics::multiplyScalar(totalDifferenceVector, 1.f / this->closeBoids.size());
	MathAndPhysics::Vector optimalVelocity = MathAndPhysics::setMagnitude(averageDifference, this->maxSpeed);
	MathAndPhysics::Vector correctionForce = MathAndPhysics::subtractVectors(optimalVelocity, this->velocity);

	return correctionForce;
}

void Boid::calculateFNet()
{
	MathAndPhysics::Vector alignForce = this->align();
	MathAndPhysics::Vector cohesionForce = this->cohesion();
	MathAndPhysics::Vector separationForce = this->separation();
	this->acceleration = MathAndPhysics::addVectors(alignForce, cohesionForce, separationForce);
}

MathAndPhysics::Vector Boid::getVelocity()
{
	return this->velocity;
}

MathAndPhysics::Vector Boid::getPosition()
{
	return this->position;
}