#include "GameUI.h"
#include <dinput.h>

GameUI::GameUI(IDirect3DDevice9* device) : d3dDevice(device), currentState(UIState::MAIN_MENU), selectedItemIndex(0) {
    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create sprite\n");
    }
    else {
        OutputDebugStringA("Sprite created successfully\n");
    }

    hr = D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create font\n");
    }
    else {
        OutputDebugStringA("Font created successfully\n");
    }
}

GameUI::~GameUI() {
    if (sprite) sprite->Release();
    if (font) font->Release();
}

void GameUI::Initialize() {
    menuItems = { "Start Game", "Game Settings", "Exit" };
}

void GameUI::Update(const BYTE* diKeys) {
    bool upPressed = false;
    bool downPressed = false;
    bool enterPressed = false;

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

    if (diKeys[DIK_RETURN] & 0x80) {
        if (!enterPressed) {
            switch (currentState) {
            case UIState::MAIN_MENU:
                if (selectedItemIndex == 0) { 
                    SetState(UIState::IN_GAME);
                }
                else if (selectedItemIndex == 1) {
                    SetState(UIState::GAME_SETTINGS);
                }
                else if (selectedItemIndex == 2) {
                    PostQuitMessage(0);
                }
                break;
            }
            enterPressed = true;
        }
    }
    else {
        enterPressed = false;
    }
}

void GameUI::Render() {
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();

    HRESULT hr = sprite->Begin(D3DXSPRITE_ALPHABLEND);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to begin sprite\n");
        return;
    }

    for (size_t i = 0; i < menuItems.size(); ++i) {
        RECT textRect = { 0, 0, 0, 0 };
        D3DCOLOR color = (i == selectedItemIndex) ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255);

        // Calculate the text rectangle to get its width and height
        font->DrawText(NULL, menuItems[i].c_str(), -1, &textRect, DT_CALCRECT, color);

        // center text
        int textWidth = textRect.right - textRect.left;
        int textHeight = textRect.bottom - textRect.top;

        // text position
        D3DXVECTOR3 position((1080 - textWidth) / 2.0f, (720 / 2.0f) + (i * 60.0f) - (menuItems.size() * 30.0f), 0.0f);

        // set text rect
        textRect.left = static_cast<LONG>(position.x);
        textRect.top = static_cast<LONG>(position.y);
        textRect.right = textRect.left + textWidth;
        textRect.bottom = textRect.top + textHeight;

        // draw text
        hr = font->DrawText(sprite, menuItems[i].c_str(), -1, &textRect, DT_NOCLIP, color);
    }

    sprite->End();

    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void GameUI::SetState(UIState newState) {
    currentState = newState;
    OutputDebugStringA("UI State changed\n"); 
}