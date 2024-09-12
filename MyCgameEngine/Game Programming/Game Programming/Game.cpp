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

	pGameUI = new GameUI(pGraphics->d3dDevice);
	pGameUI->Initialize();


	

	////initialize (sprites)
	//gameObjects.push_back(new Sprite());
	// gameObjects[0]->setPosition(100, 100);
}

void Game::update()
{
	while (pWindow->windowIsRunning()) {
		pInput->update();
		pGameUI->Update(pInput->getKeyboardState());
		pGraphics->clearBuffer();
		pGraphics->beginScene();

		if (pGameUI->GetState() == UIState::MAIN_MENU) {
			pGameUI->Render(); // render menu
		}
		else if (pGameUI->GetState() == UIState::IN_GAME) {
			for (auto obj : gameObjects) {
				obj->render(pGraphics->d3dDevice); //rendergame
			}
		}
		pGraphics->endScene();
		pGraphics->presentScene();
	}
}

void Game::release()
{
	pManager->release();
	pInput->release();
	//GameSound::Release();
	pGraphics->cleanupGraphics();
	pWindow->cleanupWindow();

	delete pGameUI;
	for (auto obj : gameObjects) {
		delete obj;
	}
}
