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
	bool isCollide(SpaceShip* spaceShip );
	void inside(SpaceShip* spaceShip, RECT* field,D3DXVECTOR3* position);
	void inside(Ball* ball, RECT* field, D3DXVECTOR3* position);
	bool leftGoal(Ball* ball, RECT* goal, D3DXVECTOR3* position);
	bool rightGoal(Ball* ball, RECT* goal,  D3DXVECTOR3* position);
	void Circle(SpaceShip* spaceShip,SpaceShip* OtherSpaceShip);
	void Circle(SpaceShip* spaceShip, Ball* ball);
};

