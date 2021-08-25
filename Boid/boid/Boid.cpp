#include "Boid.h"

using namespace MathAndPhysics;

Boid::Boid(int screenWidth, int screenHeight, SDL_Texture* boidTexture) 
	: originalBoidTexture(boidTexture), currentBoidTexture(boidTexture)
{
	this->position = randomPositionVector(screenWidth, screenHeight);
	this->velocity = randomVector(this->maxSpeed / 5);
	this->acceleration = randomVector(this->maxAcceleration);
}

Boid::Boid(double x, double y, SDL_Texture* boidTexture)
	: originalBoidTexture(boidTexture), currentBoidTexture(boidTexture)
{
	this->position = Vector(x, y);
	this->velocity = randomVector(this->maxSpeed / 5);
	this->acceleration = randomVector(this->maxAcceleration);
}

void Boid::update(float deltaTime, int screenWidth, int screenHeight, std::vector<Boid> boids, std::vector<Obstacle> obstacles, SDL_Renderer* renderer)
{
	this->getCloseObstacles(obstacles);
	this->getCloseBoids(boids);
	this->calculateFNet();
	this->applyImpulse(deltaTime, screenWidth, screenHeight);
	this->closeBoids.clear();
	this->obstaclesInSight.clear();
	this->renderBoid(renderer);
}

void Boid::renderBoid(SDL_Renderer* renderer)
{
	SDL_Rect position = { (int)this->position.x, (int)this->position.y, this->width, this->height };
	SDL_RenderCopyEx(renderer, this->currentBoidTexture, NULL, &position, this->velocity.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
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
	Vector correctedAcceleration = multiplyScalar(this->acceleration, this->friction * deltaTime);
	this->velocity = addVectors(this->velocity, correctedAcceleration);
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
	this->velocity.angle = findAngleRadians(this->velocity.y, this->velocity.x);
}

void Boid::updatePosition(float deltaTime)
{
	Vector correctedVelocity = multiplyScalar(this->velocity, deltaTime);
	this->position = addVectors(this->position, this->velocity);
}

void Boid::getCloseBoids(std::vector<Boid> &boids)
{
	for (size_t i = 0; i < boids.size(); ++i)
	{
		Vector candidateBoidPosition = boids[i].getPosition();
		double distanceAway = distance(this->position.x, this->position.y, candidateBoidPosition.x, candidateBoidPosition.y);
		Vector pointingTowardsClose = subtractVectors(candidateBoidPosition, this->position);
		double angleToCheck = pointingTowardsClose.angle * (180 / M_PI);
		double currentVelocityAngle = this->velocity.angle;

		if (distanceAway != 0 && distanceAway < this->distanceConsideredClose && abs(angleToCheck - currentVelocityAngle) < 150)
		{
			this->currentBoidTexture = boids[i].getTexture();
			this->closeBoids.push_back(boids[i]);
		}
	}
}

void Boid::getCloseObstacles(std::vector<Obstacle>& obstacles)
{
	for (size_t i = 0; i < obstacles.size(); ++i)
	{
		Vector possibleObstaclePosition = obstacles[i].getPosition();
		double distanceAway = distance(this->position.x, this->position.y, possibleObstaclePosition.x, possibleObstaclePosition.y);

		if (distanceAway != 0 && distanceAway < this->distanceObstacleConsideredClose)
		{
			this->obstaclesInSight.push_back(obstacles[i]);
		}
	}
	if (this->obstaclesInSight.empty())
	{
		this->currentBoidTexture = this->originalBoidTexture;
	}
}

Vector Boid::align()
{
	if (closeBoids.empty())
	{
		return randomVector(this->maxAcceleration);
	}

	Vector totalVelocityVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		Vector closeBoidVelocity = closeBoids[i].getVelocity();
		totalVelocityVector = addVectors(totalVelocityVector, closeBoidVelocity);
	}
	Vector averageVelocity = multiplyScalar(totalVelocityVector, 1.f / closeBoids.size());
	Vector correctedAverage = setMagnitude(averageVelocity, this->maxSpeed);
	Vector correctionForce = subtractVectors(correctedAverage, this->velocity);

	return correctionForce;
}

Vector Boid::cohesion()
{
	if (closeBoids.empty())
	{
		return randomVector(this->maxAcceleration);
	}

	Vector totalPositionVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		Vector closeBoidsPosition = this->closeBoids[i].getPosition();
		totalPositionVector = addVectors(totalPositionVector, closeBoidsPosition);
	}
	Vector averagePosition = multiplyScalar(totalPositionVector, 1.f / this->closeBoids.size());
	Vector correctionDirection = subtractVectors(averagePosition, this->position);
	Vector optimalVelocity = setMagnitude(correctionDirection, this->maxSpeed);
	Vector correctionForce = subtractVectors(optimalVelocity, this->velocity);

	return correctionForce;
}

Vector Boid::separation()
{
	if (closeBoids.empty())
	{
		return randomVector(this->maxAcceleration);
	}

	Vector totalDifferenceVector;
	for (int i = 0; i < this->closeBoids.size(); i++)
	{
		Vector closeBoidsPosition = this->closeBoids[i].getPosition();
		double distanceFromSelf = distance(this->position.x, this->position.y, closeBoidsPosition.x, closeBoidsPosition.y);
		Vector differenceVector = subtractVectors(this->position, closeBoidsPosition);
		Vector correctedDifference = multiplyScalar(differenceVector, 1.f / pow(distanceFromSelf, 2));
		totalDifferenceVector = addVectors(totalDifferenceVector, correctedDifference);
	}
	Vector averageDifference = multiplyScalar(totalDifferenceVector, 1.f / this->closeBoids.size());
	Vector optimalVelocity = setMagnitude(averageDifference, this->maxSpeed);
	Vector correctionForce = subtractVectors(optimalVelocity, this->velocity);

	return correctionForce;
}

Vector Boid::avoidObstacles()
{
	if (this->obstaclesInSight.empty())
	{
		return Vector();
	}

	Vector totalDifferenceVector;
	for (int i = 0; i < this->obstaclesInSight.size(); i++)
	{
		Vector closeObstaclesPosition = this->obstaclesInSight[i].getPosition();
		double distanceFromSelf = distance(this->position.x, this->position.y, closeObstaclesPosition.x, closeObstaclesPosition.y);
		Vector differenceVector = subtractVectors(this->position, closeObstaclesPosition);
		Vector correctedDifference = multiplyScalar(differenceVector, 1.f / pow(distanceFromSelf, 2));
		totalDifferenceVector = addVectors(totalDifferenceVector, correctedDifference);
	}
	Vector averageDifference = multiplyScalar(totalDifferenceVector, 1.f / this->obstaclesInSight.size());
	Vector optimalVelocity = setMagnitude(averageDifference, this->maxSpeed);
	Vector correctionForce = subtractVectors(optimalVelocity, this->velocity);

	return correctionForce;
}

void Boid::calculateFNet()
{
	Vector alignForce = this->align();
	Vector cohesionForce = this->cohesion();
	Vector separationForce = this->separation();
	Vector obstacleAvoidanceForce = this->avoidObstacles();
	Vector correctedObstacleAvoidanceForce = multiplyScalar(obstacleAvoidanceForce, 20);
	this->acceleration = addVectors(alignForce, cohesionForce, separationForce, correctedObstacleAvoidanceForce);
}

Vector Boid::getVelocity()
{
	return this->velocity;
}

Vector Boid::getPosition()
{
	return this->position;
}

SDL_Texture* Boid::getTexture()
{
	return this->currentBoidTexture;
}