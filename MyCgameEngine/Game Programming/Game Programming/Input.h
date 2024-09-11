#pragma once
#include<dinput.h>
#include"Window.h"
class Input
{
public:
	static Input* getInstance();
	bool createInput();
	void update();
	void release();
	bool EscapeKeyPressed();
	bool MouseButtonPressed(int button);
	bool MouseButtonClick(int button);
	bool KeyboardKeyHold(int code);
	bool KeyboardKeyPressed(int code);
	bool ReadKeyboard();
	bool ReadMouse();
private:
	Input();
	~Input();
	static Input* instance;
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8  dInputMouseDevice;
	BYTE  diKeys[256];
	DIMOUSESTATE mouseState;
	int previousKeyState[256];
	int previousMouseState[3];
	struct mousePosition {
		int x;
		int y;
	} mousePosition;
};

