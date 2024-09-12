#include "Field1.h"

Field1::Field1()
{
	sprite = NULL;
	texture = NULL;
}

Field1::~Field1()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	gameObjects.clear();
}

void Field1::init()
{
}

void Field1::update()
{
}

void Field1::draw()
{
}

void Field1::release()
{
}

