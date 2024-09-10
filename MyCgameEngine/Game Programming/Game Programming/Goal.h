#pragma once
#include <Windows.h>
class Goal
{
public:
	Goal(int top, int bottom, int left, int right);
	RECT* GetRect();
private :
	RECT rect;
};

