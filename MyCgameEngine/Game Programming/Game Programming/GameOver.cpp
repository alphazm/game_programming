#include "GameOver.h"
#include <dinput.h>

GameOver::GameOver(IDirect3DDevice9* dev) : device(dev), sprite(nullptr), font(nullptr), winningPlayer(0), selectedOption(0) {}

GameOver::~GameOver() {
    release();
}

void GameOver::init() {
    Initialize();
}

void GameOver::Initialize() {
    HRESULT hr = D3DXCreateTextureFromFile(device, "assets/Window.png", &popupTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load popup texture\n");
    }
    D3DXCreateSprite(device, &sprite);
    D3DXCreateFont(device, 36, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
}

void GameOver::update() {
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;
    static DWORD lastKeyPressTime = 0;
    const DWORD KEY_DELAY = 200; 
    DWORD currentTime = GetTickCount64();
    if (currentTime - lastKeyPressTime > KEY_DELAY) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (!upPressed) {
                selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
                upPressed = true;
                lastKeyPressTime = currentTime;
            }
        }
        else {
            upPressed = false;
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (!downPressed) {
                selectedOption = (selectedOption + 1) % totalOptions;
                downPressed = true;
                lastKeyPressTime = currentTime;
            }
        }
        else {
            downPressed = false;
        }

        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!enterPressed) {
                enterPressed = true;
                lastKeyPressTime = currentTime;
                switch (selectedOption) {
                case 0:
                    // restart
                    break;
                case 1:
                    // main menu
                    break;
                case 2:
                    PostQuitMessage(0);
                    break;
                }
            }
        }
        else {
            enterPressed = false;
        }
    }
}

void GameOver::draw() {
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    if (popupTexture) {
        D3DXVECTOR3 pos(600, 200, 0);
        RECT windowRect = { 0, 0, 940, 800 };

        D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1.0f);
        sprite->SetTransform(&scaleMatrix);

        sprite->Draw(popupTexture, &windowRect, NULL, &pos, D3DCOLOR_ARGB(255, 255, 255, 255)); 

        D3DXMatrixIdentity(&identityMatrix);
        sprite->SetTransform(&identityMatrix);
    }

    std::string gameOverText = "GAME OVER";
    std::string winnerText = "Player " + std::to_string(winningPlayer) + " Wins!";

    RECT textRect = { 200, 110, 840, 200 };
    RECT winnerRect = { 200, 200, 840, 300 };
    font->DrawText(sprite, gameOverText.c_str(), -1, &textRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
    font->DrawText(sprite, winnerText.c_str(), -1, &winnerRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
    std::string options[] = { "Replay", "Main Menu", "Quit" };
    for (int i = 0; i < totalOptions; ++i) {
        D3DCOLOR color = (i == selectedOption) ? D3DCOLOR_XRGB(255, 255, 0) : D3DCOLOR_XRGB(255, 255, 255);
        RECT optionRect = { 200, 300 + i * 50, 840, 400 + i * 50 };
        font->DrawText(sprite, options[i].c_str(), -1, &optionRect, DT_CENTER, color);
    }

    sprite->End();
}

void GameOver::release() {
    if (sprite) {
        sprite->Release();
        sprite = nullptr;
    }
    if (font) {
        font->Release();
        font = nullptr;
    }
    if (popupTexture) popupTexture->Release();
}

void GameOver::SetWinningPlayer(int player) {
    winningPlayer = player;
}

