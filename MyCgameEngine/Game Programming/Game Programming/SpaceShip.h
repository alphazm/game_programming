#pragma once
#include <d3dx9.h>
#include "SpriteRender.h"
#include "Friction.h"
enum Key {UP,LEFT,RIGHT,DOWN};

class SpaceShip:public SpriteRender
{
public:
	~SpaceShip();
	void setMass(float mass);
	void setRotateSpeed(float rotationSpeed);
	void setInitialForce(float value);
	void setAcceleration(D3DXVECTOR2 accelerate);
	void Move(Key key);
	void setFiction(float friction);
	void updatePosition();
	void setPosition(D3DXVECTOR2 position);
	void setVector(D3DXVECTOR2 vector);
	D3DXVECTOR2 getPosition();
	D3DXVECTOR2 getVector();
	float getMass();
	
private:
	float mass;
	float rotationSpeed;
	float initialforce;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	D3DXVECTOR2 accelerate;
	float friction;
};

