#pragma once
#include <Windows.h>

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
};

