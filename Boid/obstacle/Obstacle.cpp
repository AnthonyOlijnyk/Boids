#include "Obstacle.h"

using namespace MathAndPhysics;

Obstacle::Obstacle(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;
	this->position = Vector((double)x, (double)y);
}

void Obstacle::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &this->rect);
}

Vector Obstacle::getPosition()
{
	return this->position;
}
