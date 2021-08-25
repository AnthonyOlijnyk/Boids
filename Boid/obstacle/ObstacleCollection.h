#pragma once
#include "Obstacle.h"
#include <vector>

class ObstacleCollection
{
private:
	std::vector<Obstacle> obstacleCollection;

public:
	ObstacleCollection(size_t numberOfObstacles, int screenWidth, int screenHeight, int rectWidth, int rectHeight);
	ObstacleCollection();
	Obstacle* getObstacle(int index);
	std::vector<Obstacle> getObstacleCollection();
	void renderObstacles(SDL_Renderer* renderer);
	void addObstacle(int x, int y, int w, int h);
	void clearObstacles();
	void removeLast();
};

