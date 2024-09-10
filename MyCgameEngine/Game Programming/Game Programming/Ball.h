#pragma once
#include"SpriteRender.h"

class Ball:public SpriteRender
{
public:
	~Ball();
	void setMass(float mass);
	void changeDirection();
	void setFiction(float friction);
	void updatePosition();
	void setPosition(D3DXVECTOR2 position);
	void setVector(D3DXVECTOR2 vector);
	D3DXVECTOR2 getPosition();
	D3DXVECTOR2 getVector();
	float getMass();
	
private:
	float mass;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	float angle;
	float friction;
};

