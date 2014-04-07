#ifndef LEVEL1_H
#define LEVEL1_H

#include "ObstacleMap.h"
#include "Player.h"

class Level1
{
private:
	ObstacleMap map;
	Player *player;
public:
	Level1();
	void Update();
};
#endif