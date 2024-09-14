#include "Game.h"

void Game::init()
{
	pWindow = pWindow->getInstance();
	pWindow->createWindow();
	pGraphics = pGraphics->getInstance();
	pGraphics->createDevice();
	pInput = pInput->getInstance();
	pInput->createInput();
	//GameSound::Initialize();
	pManager = pManager->getInstance();
	pManager->init();
}

void Game::update()
{
	while (pWindow->windowIsRunning()) {
		pInput->update();
		pManager->update();
		//GameSound::Update();
		pGraphics->beginScene();
		pManager->draw();
		pGraphics->endScene();
	}
}

void Game::release()
{
	pManager->release();
	pInput->release();
	//GameSound::Release();
	pGraphics->cleanupGraphics();
	pWindow->cleanupWindow();
}
