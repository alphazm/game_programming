#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

class MainMenu {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    LPDIRECT3DTEXTURE9 logoTexture;
    std::vector<std::string> menuItems;
    int selectedItemIndex;

    int originalWidth = 512;
    int originalHeight = 512;
    float scaleX = 1.25f;
    float scaleY = 1.25f;
    int newWidth;
    int newHeight;
    D3DXMATRIX scaleMatrix;

public:
    MainMenu(IDirect3DDevice9* device);
    ~MainMenu();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    int GetSelectedIndex() const { return selectedItemIndex; }
};