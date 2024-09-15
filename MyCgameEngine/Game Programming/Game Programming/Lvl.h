#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "AudioManager.h"
class Lvl
{
private:
    IDirect3DDevice9* d3dDevice;
    AudioManager* myAudioManager;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    LPD3DXSPRITE sprite;

public:
    Lvl(IDirect3DDevice9* device, AudioManager* audioManager);
    ~Lvl();
    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
};

