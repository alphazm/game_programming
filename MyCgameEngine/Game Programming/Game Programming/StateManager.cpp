#include "stateManager.h"

StateManager* StateManager::instance = 0;

StateManager* StateManager::getInstance()
{
	if (!instance)
	{
		instance = new StateManager;
	}
	return instance;
}

void StateManager::init()
{
	Field1* field1 = new Field1();
	scene.push_back(field1);
	currentState = scene[0];
	pTimer = new FrameTimer;
	pTimer->Init(30);
	elapsedTime = 0;
}

void StateManager::update()
{
	int framesToUpdate = pTimer->FramesToUpdate();
	for (int i = 0; i < framesToUpdate; i++)
	{
		elapsedTime += (1.0f / FPS);
		currentState->update();
	}
}

void StateManager::draw()
{
	currentState->draw();
}

void StateManager::release()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void StateManager::changeGameState(int index)
{
	currentState = scene[index];
}

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	scene.clear();
	currentState = NULL;
	delete pTimer;
	pTimer = NULL;
}
