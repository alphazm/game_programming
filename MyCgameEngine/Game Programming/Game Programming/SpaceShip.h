#pragma once
#include <d3dx9.h>
#include"FrameTimer.h"
#include"GameObject.h"

class SpaceShip:public GameObject
{
public:
	SpaceShip();
	~SpaceShip();
	void Initialize(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE sprite, D3DXVECTOR2 objectPosition, int objectNumber);
	void Update();
	void SetTransformation();
	void Draw();
	void setFriction(float value);
	void setRotation(float value);
	void setPlayerNumber(int value);
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	FrameTimer* timer;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 force;
	float mass;
	int player;
	int frameCounter;
	int maxFrame;
	int divisor;
	float enginePower;
	float friction;
	float rotationSpeed;
};

