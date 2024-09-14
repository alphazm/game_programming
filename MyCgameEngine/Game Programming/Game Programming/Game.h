#pragma once
#include"Window.h"
#include"Graphics.h"
#include"Input.h"
#include"StateManager.h"
class Game
{
public:
	void init();
	void update();
	void release();
private:
	Window* pWindow;
	Graphics* pGraphics;
	Input* pInput;
	StateManager* pManager;
};

