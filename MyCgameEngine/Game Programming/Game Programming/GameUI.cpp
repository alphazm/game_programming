#include "GameUI.h"
#include <dinput.h>

GameUI::GameUI(IDirect3DDevice9* device) : d3dDevice(device), currentState(UIState::MAIN_MENU) {
    mainMenu = new MainMenu(device);
}

GameUI::~GameUI() {
    delete mainMenu;
}

void GameUI::Initialize() {
    mainMenu->Initialize();
}

void GameUI::Update(const BYTE* diKeys) {
    switch (currentState) {
    case UIState::MAIN_MENU:
        mainMenu->Update(diKeys);
        if (diKeys[DIK_RETURN] & 0x80) {
            int selectedIndex = mainMenu->GetSelectedIndex();
            if (selectedIndex == 0) {
                SetState(UIState::IN_GAME);
            }
            else if (selectedIndex == 1) {
                SetState(UIState::GAME_SETTINGS);
            }
            else if (selectedIndex == 2) {
                PostQuitMessage(0);
            }
        }
        break;
    }
}

void GameUI::Render() {
    switch (currentState) {
    case UIState::MAIN_MENU:
        mainMenu->Render();
        break;
    }
}

void GameUI::SetState(UIState newState) {
    currentState = newState;
    OutputDebugStringA("UI State changed\n");
}