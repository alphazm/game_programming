#pragma once
#include"Window.h"
#include"Graphics.h"
#include"Input.h"
#include"StateManager.h"
#include "GameUI.h"
#include "Sprite.h"
#include "FrameTimer.h"
#include <vector>
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
	GameUI* pGameUI;
	std::vector<Sprite*> gameObjects;
	FrameTimer* pFrameTimer;
};

