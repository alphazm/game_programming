#include "Window.h"

Window* Window::instance = 0;

Window* Window::getInstance()
{
	if (!instance)
	{
		instance = new Window;
	}
	return instance;
}



LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = Window::getInstance();
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F11:
			if (pWindow) {
				pWindow->fullscreenHandle();  
			}
			break;
		default:
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::createWindow()
{
	WNDCLASS wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Spaceship Football", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, wndClass.hInstance, NULL);
	ShowWindow(g_hWnd, 1);
	ShowCursor(false);
	GetWindowRect(g_hWnd, &windowRect);
	ZeroMemory(&msg, sizeof(msg));
}

bool Window::windowIsRunning()
{
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

HWND Window::getHWND()
{
    return this->g_hWnd;
}

Window::Window()
{
}

Window::~Window()
{
	
}

void Window::cleanupWindow()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
	delete instance;
	instance = 0;
}

void Window::fullscreenHandle()
{
	if (g_fullscreen) {
		// Restore window
		SetWindowLong(g_hWnd, GWL_STYLE, g_dwStyle);
		SetWindowPlacement(g_hWnd, &g_wpPrev);
		SetWindowPos(g_hWnd, nullptr, 0, 0, 0, 0,
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
	else {
		// Save current window state
		g_dwStyle = GetWindowLong(g_hWnd, GWL_STYLE);
		GetWindowPlacement(g_hWnd, &g_wpPrev);

		// Make window borderless and go fullscreen
		SetWindowLong(g_hWnd, GWL_STYLE, g_dwStyle & ~WS_OVERLAPPEDWINDOW);
		MONITORINFO mi = { sizeof(mi) };
		if (GetMonitorInfo(MonitorFromWindow(g_hWnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowPos(g_hWnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	}
	g_fullscreen = !g_fullscreen;
}
