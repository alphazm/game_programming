#pragma once
#include"FrameTimer.h"
#include"GameObject.h"

class Ball :public GameObject
{
public:
	Ball();
	~Ball();
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 objectPosition, int objectNumber);
	void Update();
	void SetTransformation();
	void Draw();
	void changeDirection();
	float mass;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	FrameTimer* timer;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 position;
	float friction;
	int frameCounter;
	int maxFrame;
	int divisor;

};

