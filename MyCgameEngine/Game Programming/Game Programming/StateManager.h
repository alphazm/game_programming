#pragma once
#include<vector>
#include "FrameTimer.h"
#include "State.h"
#include "MainMenu.h"
#include "Field1.h"
#define FPS 30.0f
using namespace std;

class StateManager
{
public:
	static StateManager* getInstance();
	void init();
	void update();
	void draw();
	void release();
	float elapsedTime;
	FrameTimer* pTimer;
	State* currentState;
	vector<State*> scene;
	void changeGameState(int index);
private:
	static StateManager* instance;
	StateManager();
	~StateManager();
};

