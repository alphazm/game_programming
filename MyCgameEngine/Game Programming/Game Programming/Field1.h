#pragma once
#include "State.h"
#include "StateManager.h"
#include "SpaceShip.h"
#include "Ball.h"
#include "collider.h"
#include "Goal.h"
#include "Input.h"
using namespace std;

class Field1 : public State
{
public:
	Field1();
	~Field1();
	void init();
	void update();
	void draw();
	void release();

private:
	SpaceShip* player1;
	SpaceShip* player2;
	Ball* ball;
	Input* input;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	Goal* gate1;
	Goal* gate2;
	RECT field;
	vector<GameObject*> gameObjects;
};

