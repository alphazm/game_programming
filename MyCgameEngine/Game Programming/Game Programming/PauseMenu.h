#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

class PauseMenu {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    std::vector<std::string> menuItems;
    int selectedItemIndex;

public:
    PauseMenu(IDirect3DDevice9* device);
    ~PauseMenu();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    int GetSelectedIndex() const { return selectedItemIndex; }
};