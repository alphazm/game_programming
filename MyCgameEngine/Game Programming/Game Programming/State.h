#pragma once
class State
{
public:
	virtual ~State();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void release() = 0;
};

