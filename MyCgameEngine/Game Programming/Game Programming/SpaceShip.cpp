#include "SpaceShip.h"
#include <iostream>

SpaceShip::SpaceShip()
{
	texture = NULL;
	sprite = NULL;
}
SpaceShip::~SpaceShip()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	delete timer;
	timer = NULL;
}

void SpaceShip::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 startingPosition, int objectNumber)
{
	HRESULT hr = D3DXCreateSprite(device, &sprite);
	hr = D3DXCreateTextureFromFile(device,"assets/spaceShip.png", &texture);
	textureHeight = 64;
	textureWidth = 64;
	textureCol = 2;
	textureRow = 2;
	maxFrame = 2;
	spriteCurrentFrame = 0;
	spriteWidth = textureWidth / textureCol;
	spriteHeight = textureHeight / textureRow;
	divisor = 4;
	position = startingPosition;
	scaling = { 1.0f,1.0f };
	scalingCenter = { 0,0 };
	spriteCenter = { (float)spriteWidth / 2,(float)spriteHeight / 2 };
	scalingRotation = 0.0f;
	rotation = 0.0;
	player = 0;
	object = objectNumber;
	direction = { 0,0 };
	acceleration = { 0,0 };
	velocity = { 0,0 };
	rotationSpeed = 0.25f;
	mass = 100;
	enginePower = 200;
	friction = 0.0f;
}

void SpaceShip::Update()
{

		frameCounter++;
		if (frameCounter % divisor == 0) {
			spriteCurrentFrame++;
		}
		if (spriteCurrentFrame > maxFrame)
		{
			spriteCurrentFrame = 0;
		}

	spriteRect.left = spriteWidth * player;
	spriteRect.top = spriteCurrentFrame % textureRow * (spriteHeight);
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.bottom = spriteRect.top + spriteHeight;
}

void SpaceShip::SetTransformation()
{
	D3DXMatrixTransformation2D(&mat, &scalingCenter, scalingRotation, &scaling, &spriteCenter, rotation, &position);
	sprite->SetTransform(&mat);
}

void SpaceShip::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransformation();
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void SpaceShip::setFriction(float value)
{
	this->friction = value;
}

void SpaceShip::setRotation(float value)
{
	this->rotation = value;
}

void SpaceShip::setPlayerNumber(int value)
{
	this->player = value;
}






