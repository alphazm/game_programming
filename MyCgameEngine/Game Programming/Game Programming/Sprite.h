#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
class Sprite
{
public:
	Sprite();
	~Sprite();
	int textureHeight;
	int textureWidth;
	int textureCol;
	int textureRow;
	int maxFrame;
	int spriteCurrentFrame;
	int spriteWidth;
	int spriteHeight;
	RECT spriteRect;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 position;

	void setTexture(LPDIRECT3DTEXTURE9 texture);
	void setPosition(float x, float y);
	void update();
	void render(IDirect3DDevice9* d3dDevice);

};


