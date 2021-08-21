#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>


class Boid
{
private:
	float xPosition = 0;
	float yPosition = 0;
	float xVelocity = 2000;
	float yVelocity = 2000;
	float xAcceleration = 1000;
	float yAcceleration = 1000;
	const float maxSpeed = 2000;
	const float friction = 0.9;
	const float distanceConsideredClose = 100;
	double angle;
	const int width = 20;
	const int height = 20;
	SDL_Texture* boidTexture;
	std::vector<Boid> closeBoids;
	
public:
	Boid(float xPosition, float yPosition, float xVelocity, float yVelocity, double angle, SDL_Texture* boidTexture);
	void update(float deltaTime, int width, int height, std::vector<Boid> boids, SDL_Renderer* renderer);
	void renderBoid(SDL_Renderer* renderer);
	void checkBounds(int width, int height);
	void generateRandomImpulse();
	void applyImpulse(float deltaTime);
	void updateVelocity(float deltaTime);
	void limitVelocity();
	void updatePosition(float deltaTime);
	void getCloseBoids(std::vector<Boid> &boids);
	void align();
	float getXPosition();
	float getYPosition();
	float getXVelocity();
	float getYVelocity();
	double getAngle();
};

