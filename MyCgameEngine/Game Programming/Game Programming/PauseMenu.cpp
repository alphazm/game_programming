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
    if (pauseTexture) pauseTexture->Release();
}

void PauseMenu::Initialize() {
    /*myAudioManager->initialize();
    myAudioManager->loadSounds();*/
    menuItems = { "Resume", "Restart", "Settings", "Main Menu" };
    D3DXCreateTextureFromFile(d3dDevice, "assets/Window.png", &backgroundTexture);
    D3DXCreateTextureFromFile(d3dDevice, "assets/Header.png", &pauseTexture);
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "assets/Header.png", &pauseTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load pause texture\n");
    }
}

void PauseMenu::Update(const BYTE* diKeys) {
    static bool upPressed = false;
    static bool downPressed = false;

    if (diKeys[DIK_UP] & 0x80) {
        if (!upPressed) {
            selectedItemIndex = (selectedItemIndex - 1 + menuItems.size()) % menuItems.size();
            upPressed = true;
        }
    }
    else {
        upPressed = false;
    }

    if (diKeys[DIK_DOWN] & 0x80) {
        if (!downPressed) {
            selectedItemIndex = (selectedItemIndex + 1) % menuItems.size();
            downPressed = true;
        }
    }
    else {
        downPressed = false;
    }
}

void PauseMenu::Render() {
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    if (backgroundTexture) {
        D3DXVECTOR3 center(1000, 200, 0);
        RECT destRect = { 0, 0, 940, 800 };
        D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1.0f);
        sprite->SetTransform(&scaleMatrix);

        sprite->Draw(backgroundTexture, &destRect, NULL, &center, D3DCOLOR_XRGB(255, 255, 255)); 
        D3DXMatrixIdentity(&identityMatrix);
        sprite->SetTransform(&identityMatrix);
    
    }

    if (pauseTexture) {
        D3DXVECTOR3 pausePos(800, 300, 0);
        RECT pauseRect = { 0, 0, 300, 59 };


        D3DXMatrixScaling(&scaleMatrix, textScaleX, textScaleY, 1.0f);
        sprite->SetTransform(&scaleMatrix);

        sprite->Draw(pauseTexture, &pauseRect, NULL, &pausePos, D3DCOLOR_XRGB(255, 255, 255));

        D3DXMatrixIdentity(&identityMatrix);
        sprite->SetTransform(&identityMatrix);
    }
 
    for (size_t i = 0; i < menuItems.size(); ++i) {
        D3DCOLOR color = (i == selectedItemIndex) ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255); 
        RECT textRect = { 350, 200 + static_cast<LONG>(i * 50), 0, 0 }; 
        font->DrawText(sprite, menuItems[i].c_str(), -1, &textRect, DT_NOCLIP, color); 
    }

    sprite->End();
}