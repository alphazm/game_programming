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
	currentState = stack[0];
	pTimer = new FrameTimer;
	pTimer->Init(30);
	elapsedTime = 0;
}

void StateManager::update()
{
}

void StateManager::draw()
{
}

void StateManager::release()
{
}

void StateManager::changeGameState(int index)
{
	currentState = stack[index];
}

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	if (!stack.empty())
	{
		stack.pop();
	}
	currentState = NULL;
	delete pTimer;
	pTimer = NULL;
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}
