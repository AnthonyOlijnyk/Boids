#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Boid.h"
#include "math.h"
#include "MathAndPhysics.h"

class Boid
{
private:
	const double maxSpeed = 6;
	const double maxAcceleration = 3;
	const double friction = 0.9;
	const double distanceConsideredClose = 50;
	const int width = 20;
	const int height = 20;
	SDL_Texture* boidTexture;
	std::vector<Boid> closeBoids;
	MathAndPhysics::Vector position;
	MathAndPhysics::Vector velocity;
	MathAndPhysics::Vector acceleration;
	
public:
	Boid(int screenWidth, int screenHeight, SDL_Texture* boidTexture);
	void update(float deltaTime, int width, int height, std::vector<Boid> boids, SDL_Renderer* renderer);
	void renderBoid(SDL_Renderer* renderer);
	void checkBounds(int width, int height);
	void applyImpulse(float deltaTime, int screenWidth, int screenHeight);
	void updateVelocity(float deltaTime);
	void limitVelocity();
	void updatePosition(float deltaTime);
	void getCloseBoids(std::vector<Boid> &boids);
	void calculateFNet();
	MathAndPhysics::Vector align();
	MathAndPhysics::Vector cohesion();
	MathAndPhysics::Vector separation();
	MathAndPhysics::Vector getVelocity();
	MathAndPhysics::Vector getPosition();
};

