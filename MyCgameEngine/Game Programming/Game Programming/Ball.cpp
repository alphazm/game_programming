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


void Ball::Initialize(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE sprite, D3DXVECTOR2 startingPosition, int objectNumber)
{
	this->sprite = sprite;
	D3DXCreateTextureFromFile(device,"assets/ball.png", &texture);
	timer = new FrameTimer;
	timer->Init(30);
	textureHeight = 64;
	textureWidth = 64;
	textureCol = 2;
	textureRow = 2;
	maxFrame = 1;
	spriteCurrentFrame = 0;
	divisor = 4;
	spriteWidth = textureWidth / textureCol;
	spriteHeight = textureHeight / textureRow;
	position = startingPosition;
	scaling = { 0.8f,0.8f };
	scalingCenter = { 0,0 };
	spriteCenter = { (float)spriteWidth / 2,(float)spriteHeight / 2 };
	scalingRotation = 0.0f;
	rotation = 0.0;
	object = objectNumber;
	acceleration = { 0,0 };
	velocity = { 0,0 };
	mass = 10;
	friction = 0.0f;
}

void Ball::Update()
{
	int fps = timer->FramesToUpdate();
	for (int i = 0; i < fps; i++)
	{
		frameCounter++;
		if (frameCounter % divisor == 0) {
			spriteCurrentFrame++;
		}
		if (spriteCurrentFrame > maxFrame)
		{
			spriteCurrentFrame = 0;
		}
	}
	spriteRect.left = spriteWidth ;
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
	//sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransformation();
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->End();
}

void Ball::changeDirection()
{
	rotation = atan2(velocity.x,velocity.y);
}

void Ball::setFriction(float value)
{
	this->friction = value;
}




