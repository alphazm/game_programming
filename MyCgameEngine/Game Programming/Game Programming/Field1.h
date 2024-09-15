#pragma once
#include "collider.h"
#include "State.h"
#include "StateManager.h"
#include "SpaceShip.h"
#include "Ball.h"
#include "collider.h"
#include "Goal.h"
#include "Input.h"
#include "Graphics.h"
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
	bool onece = true;
private:
	D3DXVECTOR3* fieldPosition;
	D3DXVECTOR3* gate1Position;
	D3DXVECTOR3* gate2Position;
	SpaceShip* player1;
	SpaceShip* player2;
	Ball* ball;
	Input* input;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture2;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT goal1;
	RECT goal2;
	RECT field;
	vector<GameObject*> gameObjects;
	collider collider;
	D3DXMATRIX mat;
	FrameTimer* timer;
	int Scorep1;
	int Scorep2;
};

