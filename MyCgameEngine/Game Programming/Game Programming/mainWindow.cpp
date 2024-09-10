#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <math.h>
#include <dinput.h>
#include "FrameTimer.h"
#include "SpaceShip.h"
#include "collider.h"
#include "AudioManager.h"
//--------------------------------------------------------------------
using namespace std;

//call the interface to use 
LPD3DXSPRITE sprite = NULL;
LPD3DXFONT font = NULL;
LPD3DXLINE line = NULL;

//	make a box to store the virtual graphic card properties
D3DPRESENT_PARAMETERS d3dPP;
//	make a pointer to virtual graphic card 
IDirect3DDevice9* d3dDevice;

//	Window handle
HWND g_hWnd = NULL;
WNDCLASS wndClass;
MSG msg;

//cursor
HCURSOR setCursor;
int mouseX = 0;
int mouseY = 0;
int startMouseX = 0;
int startMouseY = 0;

//store device state
BYTE  diKeys[256];
DIMOUSESTATE diMouse;

//	Direct Input object.
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8  dInputMouseDevice;

//full screen 
RECT windowRect;
bool g_fullscreen = false;
WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
DWORD g_dwStyle;

//frame controller
FrameTimer* gameTimer = new FrameTimer();
AudioManager* myAudioManager = new AudioManager();
SpaceShip* spaceShip1= new SpaceShip();
SpaceShip* spaceShip2 = new SpaceShip();

D3DXMATRIX mat;
collider circle = collider();
//--------------------------------------------------------------------
void fullscreenHandle() {
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

bool checkHr(HRESULT hr) {
	if (FAILED(hr))
		return false;
	else
		return true;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F11:
			fullscreenHandle();
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

void createWindow() {
	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Apex Legend", WS_OVERLAPPEDWINDOW, 0, 100, 500, 500, NULL, NULL, wndClass.hInstance, NULL);
	ShowWindow(g_hWnd, 1);
	GetWindowRect(g_hWnd, &windowRect);
	ZeroMemory(&d3dPP, sizeof(d3dPP));
}

void initial() {
	gameTimer->Init(30);
	//	Define Direct3D 9.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 500;
	d3dPP.BackBufferHeight = 500;
	d3dPP.hDeviceWindow = g_hWnd;
	//	create a direct 3d object 
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	checkHr(hr);
	checkHr(D3DXCreateSprite(d3dDevice, &sprite));
	checkHr(DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL));
	checkHr(dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL));
	checkHr(dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL));
	//space ship 1
	spaceShip1->loadTexture(d3dDevice,"assets/spaceShip.png");
	spaceShip1->initi(64,64,2,2);
	spaceShip1->setMass(10);
	spaceShip1->setMaxCount(4);
	spaceShip1->setMinCount(3);
	spaceShip1->setRotateSpeed(0.1);
	spaceShip1->setInitialForce(10);
	spaceShip1->setPosition(D3DXVECTOR2(100, 100));
	//space ship 2
	spaceShip2->loadTexture(d3dDevice, "assets/spaceShip.png");
	spaceShip2->initi(64, 64, 2, 2);
	spaceShip2->setMass(1000);
	spaceShip2->setMaxCount(2);
	spaceShip2->setMinCount(1);
	spaceShip2->setRotateSpeed(0.1);
	spaceShip2->setInitialForce(20);
	spaceShip2->setPosition(D3DXVECTOR2(200, 100));
	//sound
	myAudioManager->initialize();
	myAudioManager->loadSounds();
	
	//set cursor starting potition
	startMouseX = (windowRect.right - windowRect.left) / 2;
	startMouseY = (windowRect.bottom - windowRect.top) / 2;
	mouseX = startMouseX;
	mouseY = startMouseY;
}

void createInput() {
	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
}

bool windowISRunning() {

	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	return true;
}

void getInput() {
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &diMouse);
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
}


void update(int fps) {
	for (int i = 0; i < fps; i++) {
		//space ship 1
		
		spaceShip1->FrameUpdate();
		spaceShip1->updatePosition(windowRect);
		
		if (diKeys[DIK_W] & 0x80) {
			spaceShip1->Move(UP);
		}
		if (diKeys[DIK_S] & 0x80)
		{
			spaceShip1->Move(DOWN);
		}
		if (diKeys[DIK_A] & 0x80)
		{
			spaceShip1->Move(LEFT);
		}
		if (diKeys[DIK_D] & 0x80)
		{
			spaceShip1->Move(RIGHT);
		}
		//space ship 2
		spaceShip2->FrameUpdate();
		spaceShip2->updatePosition(windowRect);
		
		if (diKeys[DIK_UP] & 0x80) {
			spaceShip2->Move(UP);
		}
		if (diKeys[DIK_DOWN] & 0x80)
		{
			spaceShip2->Move(DOWN);
		}
		if (diKeys[DIK_LEFT] & 0x80)
		{
			spaceShip2->Move(LEFT);
		}
		if (diKeys[DIK_RIGHT] & 0x80)
		{
			spaceShip2->Move(RIGHT);
		}
		circle.sequance(spaceShip1,spaceShip2);
		
	}
}

void Render() {
	D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL,NULL);
	//Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);
	//	Begin the scene
	d3dDevice->BeginScene();
	//	Drawing.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//sprite->Draw(spaceShip1->getTexture(), spaceShip1->GetRect(), NULL, NULL,D3DCOLOR_XRGB(255,255,255));
	sprite->SetTransform(spaceShip1->getMat());
	spaceShip1->Render(sprite);
	sprite->SetTransform(spaceShip2->getMat());
	spaceShip2->Render(sprite);
	sprite->End();
	//	End the scene
	d3dDevice->EndScene();
	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void cleanupWindow() {

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	sprite->Release();
	sprite = NULL;

	delete spaceShip1;
	delete spaceShip2;

	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;
	// release mouse device
	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;

	//	Free up the memory.
	UnregisterClass("My Window", GetModuleHandle(NULL));
}

void Sound() {
	myAudioManager->updateSound();
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ZeroMemory(&msg, sizeof(msg));
	createWindow();
	initial();
	createInput();
	myAudioManager->playSoundTrack();
	while (windowISRunning())
	{
		setCursor = SetCursor(NULL);
		getInput();
		update(gameTimer->FramesToUpdate());
		//Sound()
		//Physic()
		Render();

	}
	cleanupWindow();
	return 0;
}