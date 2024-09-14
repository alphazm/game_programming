#pragma once
#include <Windows.h>
class Goal
{
public:
	Goal();
	RECT* GetRect();
private :
	RECT rect;
};

