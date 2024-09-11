#pragma once
#include<Windows.h>
#define WIN_WIDTH 720
#define WIN_HEIGHT 480
class Window
{
public:
	static Window* getInstance();
	void createWindow();
	bool windowIsRunning();
	void fullscreenHandle();
	HWND getHWND();
	Window();
	~Window();
private:
	static Window* instance;
	HINSTANCE hInstance;
	HWND g_hWnd;
	WNDCLASS wndClass;
	RECT windowRect;
	MSG msg;
	DWORD g_dwStyle;
	WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
	bool g_fullscreen = false;
	
};

