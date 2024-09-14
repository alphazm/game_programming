#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Window.h"
class Graphics
{
public:
	static Graphics* getInstance();
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3D9* direct3D9;
	IDirect3DDevice9* d3dDevice;
	void createDevice();
	void clearBuffer();
	void beginScene();
	void endScene();
	void presentScene();
	void cleanupGraphics();
private:
	static Graphics* instance;
	Graphics();
	~Graphics();
};

