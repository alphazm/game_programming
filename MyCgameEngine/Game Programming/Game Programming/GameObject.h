#pragma once
#include <d3dx9.h>
#include "Sprite.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Initialize(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE sprite, D3DXVECTOR2 objectPosition, int objectNumber) = 0;
	virtual void Update() = 0;
	virtual void SetTransformation() = 0;
	virtual void Draw() = 0;
	int object;
	//
	int textureHeight;
	int textureWidth;
	int textureCol;
	int textureRow;
	int maxFrame;
	int spriteCurrentFrame;
	int spriteWidth;
	int spriteHeight;
	RECT spriteRect;
	//matrix
	D3DXMATRIX mat;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 spriteCenter;
	float scalingRotation;
	float rotation;
};

