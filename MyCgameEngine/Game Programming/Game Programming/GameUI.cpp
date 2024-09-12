#include "GameUI.h"
#include <dinput.h>
#include <d3dx9.h> 
#include <d3d9.h>

LPDIRECT3DTEXTURE9 backgroundTexture = NULL;
LPDIRECT3DTEXTURE9 menuItemTexture = NULL;

GameUI::GameUI(IDirect3DDevice9* device) : d3dDevice(device), currentState(UIState::MAIN_MENU), selectedItemIndex(0) {
    D3DXCreateSprite(d3dDevice, &sprite);
    D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New", &font);
    D3DXCreateTextureFromFile(d3dDevice, "assets/ui/BG.png", &backgroundTexture);

}

GameUI::~GameUI() {
    if (sprite) sprite->Release();
    if (font) font->Release();
    if (backgroundTexture) backgroundTexture->Release();
}

void GameUI::Initialize() {
    menuItems.push_back({ "Start Game", D3DXVECTOR2(200, 200), true });
    menuItems.push_back({ "Game Settings", D3DXVECTOR2(200, 250), false });
    menuItems.push_back({ "Exit", D3DXVECTOR2(200, 300), false });
}

void GameUI::Update(const BYTE* diKeys) {
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;

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

    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].isSelected = (i == selectedItemIndex);
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
    switch (currentState) {
    case UIState::MAIN_MENU:
        RenderMainMenu();
        break;
    case UIState::GAME_SETTINGS:
        RenderGameSettings();
        break;
    case UIState::IN_GAME:
        RenderInGame();
        break;
    case UIState::PAUSE_MENU:
        RenderPauseMenu();
        break;
    }
}

void GameUI::SetState(UIState newState) {
    currentState = newState;
}

void GameUI::RenderMainMenu() {
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    // Draw background
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(backgroundTexture, NULL, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));

    //loop menu items and render
    for (const auto& item : menuItems) {
        // Draw menu item background
        RECT itemRect = { static_cast<LONG>(item.position.x - 10), static_cast<LONG>(item.position.y - 5),
                          static_cast<LONG>(item.position.x + 200), static_cast<LONG>(item.position.y + 35) };
        D3DXVECTOR3 itemPos((FLOAT)itemRect.left, (FLOAT)itemRect.top, 0);
        sprite->Draw(menuItemTexture, &itemRect, NULL, &itemPos,
            item.isSelected ? D3DCOLOR_ARGB(255, 255, 255, 255) : D3DCOLOR_ARGB(200, 200, 200, 200));

        // Draw text
        RECT textRect = { static_cast<LONG>(item.position.x), static_cast<LONG>(item.position.y), 0, 0 };
        font->DrawText(sprite, item.text.c_str(), -1, &textRect, DT_NOCLIP,
            item.isSelected ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255));
    }
    sprite->End();
}

void GameUI::RenderGameSettings() {
}

void GameUI::RenderInGame() {
}

void GameUI::RenderPauseMenu() {
}