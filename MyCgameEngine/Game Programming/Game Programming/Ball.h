#pragma once
#include <d3dx9.h>
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
	void setFriction(float value);
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	FrameTimer* timer;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	float mass;
	float friction;
	int frameCounter;
	int maxFrame;
	int divisor;

};

