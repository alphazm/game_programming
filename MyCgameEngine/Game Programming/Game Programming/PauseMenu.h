#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>
#include "AudioManager.h"

class PauseMenu {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    LPDIRECT3DTEXTURE9 pauseTexture;

    std::vector<std::string> menuItems;
    int selectedItemIndex;
    float scaleX = 0.3f;
    float scaleY = 0.5f;
    float textScaleX = 0.4f;
    float textScaleY = 0.4f;
    D3DXMATRIX scaleMatrix;
    D3DXMATRIX identityMatrix;
    /*AudioManager* sounds;
    AudioManager* myAudioManager = new AudioManager();*/
public:
    PauseMenu(IDirect3DDevice9* device);
    ~PauseMenu();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    int GetSelectedIndex() const { return selectedItemIndex; }
};