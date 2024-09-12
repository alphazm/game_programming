#include "Input.h"
Input* Input::instance = 0;
Input* Input::getInstance()
{
	if (!instance)
		instance = new Input;
	return instance;
}

bool Input::createInput()
{
	HRESULT result;
	DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	result = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FAILED(result))
	{
		return false;
	}
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputKeyboardDevice->SetCooperativeLevel(Window::getInstance()->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->Acquire();
	result = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FAILED(result))
	{
		return false;
	}
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(Window::getInstance()->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->Acquire();
	return true;
}

void Input::update()
{
	Input::ReadKeyboard();
	Input::ReadMouse();
	mousePosition.x += mouseState.lX;
	mousePosition.y += mouseState.lY;
	if (mousePosition.x < 0)
		mousePosition.x = 0;
	if (mousePosition.y < 0)
		mousePosition.y = 0;
	if (mousePosition.x > WIN_WIDTH)
		mousePosition.x = WIN_WIDTH;
	if (mousePosition.y > WIN_HEIGHT)
		mousePosition.y = WIN_HEIGHT;
}

void Input::release()
{
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;
	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;
	dInput->Release();
	dInput = NULL;
	delete instance;
	instance = NULL;
}

bool Input::EscapeKeyPressed()
{
	if (diKeys[DIK_ESCAPE] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::MouseButtonPressed(int button)
{
	if (mouseState.rgbButtons[button] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::MouseButtonClick(int button)
{
	if (mouseState.rgbButtons[button] & 0x80)
	{
		previousMouseState[button] = 1;
	}
	else if (previousMouseState[button] == 1)
	{
		previousMouseState[button] = 0;
		return true;
	}
	return false;
}

bool Input::KeyboardKeyHold(int code)
{
	if (diKeys[code] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::KeyboardKeyPressed(int code)
{
	if (diKeys[code] & 0x80)
	{
		previousKeyState[code] = 1;
	}
	else if (previousKeyState[code] == 1)
	{
		previousKeyState[code] = 0;
		return true;
	}
	return false;
}

Input::Input()
{
	mousePosition.x = 0;
	mousePosition.y = 0;
	ZeroMemory(diKeys, sizeof(diKeys));
	ZeroMemory(&mouseState, sizeof(mouseState));
}

Input::~Input()
{
}

bool Input::ReadKeyboard()
{
	HRESULT result;
	result = dInputKeyboardDevice->GetDeviceState(sizeof(diKeys), (LPVOID)diKeys);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			dInputKeyboardDevice->Acquire();
		else
			return false;
	}
	return true;
}

bool Input::ReadMouse()
{
	HRESULT result;
	result = dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			dInputMouseDevice->Acquire();
		else
			return false;
	}
	return true;
}

bool Input::wKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::aKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::sKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::dKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::upKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::leftKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::downKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::RightKey()
{
	if (KeyboardKeyHold(DIK_W))
		return true;
	else
		return false;
}

bool Input::leftMouseKey()
{
	if (MouseButtonClick(DIMOFS_BUTTON0))
		return true;
	else
		return false;
}

const BYTE* Input::getKeyboardState() const {
	return diKeys;
}