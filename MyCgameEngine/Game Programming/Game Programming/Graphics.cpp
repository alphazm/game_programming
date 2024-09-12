#include "Graphics.h"

Graphics* Graphics::instance = 0;

Graphics* Graphics::getInstance()
{
	if (!instance)
	{
		instance = new Graphics;
	}
	return instance;
}

void Graphics::createDevice()
{
	Window* pWindow = Window::getInstance();
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 500;
	d3dPP.BackBufferHeight = 500;
	d3dPP.hDeviceWindow = pWindow->getHWND();
	direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pWindow->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, & d3dPP, & d3dDevice);
}

void Graphics::clearBuffer()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);
}

void Graphics::beginScene()
{
	d3dDevice->BeginScene();
}

void Graphics::endScene()
{
	d3dDevice->EndScene();
}

void Graphics::presentScene()
{
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}


Graphics::Graphics()
{
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dPP, sizeof(d3dPP));
}

Graphics::~Graphics()
{
	
}

void Graphics::cleanupGraphics() {
	d3dDevice->Release();
	d3dDevice = NULL;
	direct3D9->Release();
	direct3D9 = NULL;
	delete instance;
	instance = NULL;
}