#include "ObstacleCollection.h"

ObstacleCollection::ObstacleCollection(size_t numberOfObstacles, int screenWidth, int screenHeight, int rectWidth, int rectHeight)
{
	for (size_t i = 0; i < numberOfObstacles; ++i)
	{
		int randomXPosition = rand() % screenWidth;
		int randomYPosition = rand() % screenHeight;
		this->obstacleCollection.push_back(Obstacle(randomXPosition, randomYPosition, rectWidth, rectHeight));
	}
}

ObstacleCollection::ObstacleCollection()
{
}

Obstacle* ObstacleCollection::getObstacle(int index)
{
	return &this->obstacleCollection[index];
}

std::vector<Obstacle> ObstacleCollection::getObstacleCollection()
{
	return this->obstacleCollection;
}

void ObstacleCollection::renderObstacles(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < this->obstacleCollection.size(); ++i)
	{
		this->getObstacle(i)->render(renderer);
	}
}

void ObstacleCollection::addObstacle(int x, int y, int w, int h)
{
	this->obstacleCollection.push_back(Obstacle(x, y, w, h));
}

void ObstacleCollection::clearObstacles()
{
	this->obstacleCollection.clear();
}

void ObstacleCollection::removeLast()
{
	if (this->obstacleCollection.empty())
	{
		return;
	}

	this->obstacleCollection.pop_back();
}