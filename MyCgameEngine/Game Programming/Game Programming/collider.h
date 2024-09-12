#pragma once
#include <Windows.h>
#include "SpaceShip.h"
#include "Ball.h"
#include "Goal.h"
class collider
{
public:
	collider();
	bool isCollide(RECT* button,RECT* cursor);
	void inside(SpaceShip* spaceShip, RECT* field);
	void inside(Ball* ball, RECT* field);
	bool leftGoal(Ball* ball, RECT* goal, RECT* field);
	bool rightGoal(Ball* ball, RECT* goal, RECT* field);
	void Circle(SpaceShip* spaceShip,SpaceShip* OtherSpaceShip);
	void Circle(SpaceShip* spaceShip, Ball* ball);
};

