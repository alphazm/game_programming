#include "Ball.h"

Ball::Ball()
{
	texture = NULL;
	sprite = NULL;
}

Ball::~Ball()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	delete timer;
	timer = NULL;
}


void Ball::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 startingPosition, int objectNumber)
{
	HRESULT hr = D3DXCreateSprite(device,&sprite);
	hr = D3DXCreateTextureFromFile(device,"assets/ball.png", &texture);
	textureHeight = 32;
	textureWidth = 32;
	textureCol = 1;
	textureRow = 1;
	maxFrame = 1;
	spriteCurrentFrame = 0;
	divisor = 1;
	spriteWidth = textureWidth / textureCol;
	spriteHeight = textureHeight / textureRow;
	position = startingPosition;
	scaling = { 1.0f,1.0f };
	scalingCenter = { 0,0 };
	spriteCenter = { (float)spriteWidth / 2,(float)spriteHeight / 2 };
	scalingRotation = 0.0f;
	rotation = 0.0;
	object = objectNumber;
	velocity = { 0,0 };
	mass = 20;
	friction = 0.0f;
}

void Ball::Update()
{

		frameCounter++;
		if (frameCounter % divisor == 0) {
			spriteCurrentFrame++;
		}
		if (spriteCurrentFrame > maxFrame)
		{
			spriteCurrentFrame = 0;
		}

	spriteRect.left = spriteWidth - spriteWidth;
	spriteRect.top = spriteCurrentFrame % textureRow * (spriteHeight);
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.bottom = spriteRect.top + spriteHeight;
}

void Ball::SetTransformation()
{
	changeDirection();
	D3DXMatrixTransformation2D(&mat, &scalingCenter, scalingRotation, &scaling, &spriteCenter, rotation, &position);
	sprite->SetTransform(&mat);
}

void Ball::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransformation();
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void Ball::changeDirection()
{
	rotation = atan2(velocity.x,-velocity.y);
}

void Ball::setFriction(float value)
{
	this->friction = value;
}