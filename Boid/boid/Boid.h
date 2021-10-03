#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Boid.h"
#include "math.h"
#include "MathAndPhysics.h"
#include "Obstacle.h"

class Boid
{
private:
	const double obstacleCoefficient = 8.0;
	const double alignmentCoefficient = 1.0;
	const double separationCoefficient = 1.1;
	const double cohesionCoefficient = 1.1;
	const double angleInVision = 110;
	const double randomAccelerationMagnitude = 2;
	const double maxSpeed = 20;
	const double maxAcceleration = 15;
	const double friction = 0.9;
	const double distanceConsideredClose = 80;
	const double distanceObstacleConsideredClose = 70;
	const int width = 20;
	const int height = 20;
	SDL_Texture* currentBoidTexture;
	SDL_Texture* originalBoidTexture;
	std::vector<Boid> closeBoids;
	std::vector<Obstacle> obstaclesInSight;
	MathAndPhysics::Vector position;
	MathAndPhysics::Vector velocity;
	MathAndPhysics::Vector acceleration;
	
public:
	Boid(int screenWidth, int screenHeight, SDL_Texture* boidTexture);
	Boid(double x, double y, SDL_Texture* boidTexture);
	void update(float deltaTime, int width, int height, std::vector<Boid> boids, std::vector<Obstacle> obstacles, SDL_Renderer* renderer);
	void renderBoid(SDL_Renderer* renderer);
	void checkBounds(int width, int height);
	void applyImpulse(float deltaTime, int screenWidth, int screenHeight);
	void updateVelocity(float deltaTime);
	void limitVelocity();
	void updatePosition(float deltaTime);
	void getCloseBoids(std::vector<Boid> &boids);
	void getCloseObstacles(std::vector<Obstacle>& obstacles);
	void calculateFNet();
	MathAndPhysics::Vector align();
	MathAndPhysics::Vector cohesion();
	MathAndPhysics::Vector separation();
	MathAndPhysics::Vector avoidObstacles();
	MathAndPhysics::Vector getVelocity();
	MathAndPhysics::Vector getPosition();
	SDL_Texture* getTexture();
};

