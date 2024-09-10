#include "SpaceShip.h"
#include <iostream>
using namespace std;
SpaceShip::~SpaceShip()
{
}


void SpaceShip::setMass(float mass)
{
	this->mass = mass;
}

void SpaceShip::setRotateSpeed(float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}

void SpaceShip::setInitialForce(float value)
{
	this->initialforce = value;
}

void SpaceShip::setAcceleration(D3DXVECTOR2 accelerate)
{
	this->accelerate = accelerate;
}

void SpaceShip::Move(Key key)
{
	switch (key)
	{
	case UP:
		accelerate = D3DXVECTOR2((initialforce / mass), (initialforce / mass));
		break;
	case LEFT:
		updateRotateValue(-rotationSpeed);
		break;
	case RIGHT:
		updateRotateValue(rotationSpeed);
		break;
	case DOWN:
		accelerate = D3DXVECTOR2(- (initialforce / mass),-(initialforce / mass));
		break;
	default:
		break;
	}
}

void SpaceShip::setFiction(float friction)
{
	this->friction = friction;
}

void SpaceShip::updatePosition()
{
	D3DXVECTOR2 direction = D3DXVECTOR2(-cos(getRotateValue()), -sin(getRotateValue()));
	accelerate.x *= direction.x;
	accelerate.y *= direction.y;
	velocity += accelerate;
	velocity *= friction;
	position += velocity;
	settranslation(position);
}

void SpaceShip::setPosition(D3DXVECTOR2 position)
{
	this->position = position;
	settranslation(position);
}

void SpaceShip::setVector(D3DXVECTOR2 velocity)
{
	this->velocity = velocity;
}

D3DXVECTOR2 SpaceShip::getPosition()
{
	return position;
}

D3DXVECTOR2 SpaceShip::getVector()
{
	return velocity;
}

float SpaceShip::getMass()
{
	return mass;
}




