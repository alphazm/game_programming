#pragma once
#include <stack>
#include"FrameTimer.h"
#include "State.h"
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
	stack<State> stack;
	void changeGameState(int index);
private:
	static StateManager* instance;
	StateManager();
	~StateManager();
};

