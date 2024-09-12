#pragma once
#include <d3dx9.h>
#include "Sprite.h"
class GameObject: public Sprite
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Initialize(LPDIRECT3DDEVICE9 device, float rotation, int playerNumber, D3DXVECTOR2 objectPosition, int objectNumber) = 0;
	virtual void Update() = 0;
	virtual void SetTransformation() = 0;
	virtual void Draw() = 0;
	int object;
	
	//matrix
	D3DXMATRIX mat;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 spriteCenter;
	float scalingRotation;
	float rotation;
};

