#include "PauseMenu.h"
#include <dinput.h>

PauseMenu::PauseMenu(IDirect3DDevice9* device) : d3dDevice(device), selectedItemIndex(0) {
    D3DXCreateSprite(d3dDevice, &sprite);
    D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
}

PauseMenu::~PauseMenu() {
    if (sprite) sprite->Release();
    if (font) font->Release();
    if (backgroundTexture) backgroundTexture->Release();
}

void PauseMenu::Initialize() {
    menuItems = { "Resume", "Restart", "Settings", "Main Menu" };
    D3DXCreateTextureFromFile(d3dDevice, "assets/Window.png", &backgroundTexture);
}

void PauseMenu::Update(const BYTE* diKeys) {
    if (diKeys[DIK_UP] & 0x80) {
        selectedItemIndex = (selectedItemIndex - 1 + menuItems.size()) % menuItems.size();
    }
    else if (diKeys[DIK_DOWN] & 0x80) {
        selectedItemIndex = (selectedItemIndex + 1) % menuItems.size();
    }
}

void PauseMenu::Render() {
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    if (backgroundTexture) {
        D3DXVECTOR3 center(0, 0, 0);
        RECT destRect = { 0, 0, 900, 600 };
        sprite->Draw(backgroundTexture, &destRect, NULL, &center, D3DCOLOR_XRGB(255, 255, 255)); 
    }
 
    for (size_t i = 0; i < menuItems.size(); ++i) {
        D3DCOLOR color = (i == selectedItemIndex) ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255); 
        RECT textRect = { 350, 200 + static_cast<LONG>(i * 50), 0, 0 }; 
        font->DrawText(sprite, menuItems[i].c_str(), -1, &textRect, DT_NOCLIP, color); 
    }

    sprite->End();
}