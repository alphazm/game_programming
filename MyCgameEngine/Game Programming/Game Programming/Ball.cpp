#include "Ball.h"

Ball::~Ball()
{
}

void Ball::setMass(float mass)
{
	this->mass = mass;
}

void Ball::changeDirection()
{
	angle = atan2(velocity.x,velocity.y);
	setRotateValue(angle);
}

void Ball::setFiction(float friction)
{
	this->friction = friction;
}

void Ball::updatePosition()
{
	velocity *= friction;
	position += velocity;
	settranslation(position);
}

void Ball::setPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

void Ball::setVector(D3DXVECTOR2 vector)
{
	this->velocity = vector;
}

D3DXVECTOR2 Ball::getPosition()
{
    return position;
}

D3DXVECTOR2 Ball::getVector()
{
    return velocity;
}

float Ball::getMass()
{
    return mass;
}


