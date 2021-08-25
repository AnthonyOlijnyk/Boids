#pragma once
#include <SDL.h>
#include "MathAndPhysics.h"

class Obstacle
{
private:
	SDL_Rect rect;
	int x;
	int y;
	int w;
	int h;
	MathAndPhysics::Vector position;

public:
	Obstacle(int x, int y, int width, int height);
	void render(SDL_Renderer* renderer);
	MathAndPhysics::Vector getPosition();
};

