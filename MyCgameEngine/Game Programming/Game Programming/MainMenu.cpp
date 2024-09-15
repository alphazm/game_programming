#include "MainMenu.h"
#include <dinput.h>

MainMenu::MainMenu(IDirect3DDevice9* device) : d3dDevice(device), selectedItemIndex(0) {
    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create sprite\n");
    }
    else {
        OutputDebugStringA("Sprite created successfully\n");
    }

    hr = D3DXCreateFont(d3dDevice, 40, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New", &font);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create font\n");
    }

    newWidth = static_cast<int>(originalWidth * scaleX);
    newHeight = static_cast<int>(originalHeight * scaleY);
}

MainMenu::~MainMenu() {
    if (sprite) sprite->Release();
    if (font) font->Release();
    if (backgroundTexture) backgroundTexture->Release();
    if (logoTexture) logoTexture->Release();
}

void MainMenu::Initialize() {
    menuItems = { "Start Game", "Game Settings", "Exit" };
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "assets/bg5.jpg", &backgroundTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load background texture\n");
    }
    hr = D3DXCreateTextureFromFile(d3dDevice, "assets/logo4.png", &logoTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load logo texture\n");
    }
}

void MainMenu::Update(const BYTE* diKeys) {
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

void MainMenu::Render() {
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();

    HRESULT hr = sprite->Begin(D3DXSPRITE_ALPHABLEND);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to begin sprite\n");
        return;
    }

    // Draw background
    if (backgroundTexture) {
        D3DXVECTOR3 backgroundPosition(0.0f, 0.0f, 0.0f);
        RECT destRect = { 0, 0, 900, 600 };
        sprite->Draw(backgroundTexture, &destRect, NULL, &backgroundPosition, D3DCOLOR_XRGB(255, 255, 255));
    }

    // Draw logo
    if (logoTexture) {
        D3DXVECTOR3 logoPosition((900 - newWidth) / 2.0f, 70.0f, 0.0f);
        RECT logoRect = { 0, 0, originalWidth, originalHeight };

        D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1.0f);
        sprite->SetTransform(&scaleMatrix);

        sprite->Draw(logoTexture, &logoRect, NULL, &logoPosition, D3DCOLOR_XRGB(255, 255, 255));

        D3DXMATRIX identityMatrix;
        D3DXMatrixIdentity(&identityMatrix);
        sprite->SetTransform(&identityMatrix);
    }

    // Draw menu items
    for (size_t i = 0; i < menuItems.size(); ++i) {
        RECT textRect = { 0, 0, 0, 0 };
        D3DCOLOR color = (i == selectedItemIndex) ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255);

        font->DrawText(NULL, menuItems[i].c_str(), -1, &textRect, DT_CALCRECT, color);

        int textWidth = textRect.right - textRect.left;
        int textHeight = textRect.bottom - textRect.top;

        D3DXVECTOR3 position((900 - textWidth) / 2.0f, (600 / 2.0f) + (i * 60.0f) - (menuItems.size() * 30.0f), 0.0f);

        textRect.left = static_cast<LONG>(position.x);
        textRect.top = static_cast<LONG>(position.y);
        textRect.right = textRect.left + textWidth;
        textRect.bottom = textRect.top + textHeight;

        font->DrawText(sprite, menuItems[i].c_str(), -1, &textRect, DT_NOCLIP, color);
    }

    sprite->End();
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}