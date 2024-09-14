#include "GameUI.h"
#include <dinput.h>

GameUI::GameUI(IDirect3DDevice9* device) : d3dDevice(device), currentState(UIState::MAIN_MENU) {
    myAudioManager = new AudioManager();
    mainMenu = new MainMenu(device);
    setting = new Setting(device, myAudioManager);
}

GameUI::~GameUI() {
    delete mainMenu;
    delete setting;
    delete myAudioManager;
}

void GameUI::Initialize() {
    myAudioManager->initialize();
    myAudioManager->loadSounds();
    myAudioManager->playSoundTrack();
    mainMenu->Initialize();
    setting->Initialize();
}

void GameUI::Update(const BYTE* diKeys) {
    switch (currentState) {
    case UIState::MAIN_MENU:
        mainMenu->Update(diKeys);
        if (diKeys[DIK_RETURN] & 0x80) {
            myAudioManager->playSound3();
            int selectedIndex = mainMenu->GetSelectedIndex();
            
            if (selectedIndex == 0) {
                SetState(UIState::IN_GAME);
            }
            else if (selectedIndex == 1) {
                SetState(UIState::GAME_SETTINGS);
                setting->SetMusicVolume(1.0f);
                setting->SetSoundVolume(1.0f);
                myAudioManager->setMusicVolume(1.0f);
                myAudioManager->setSoundEffectsVolume(1.0f);
            }
            else if (selectedIndex == 2) {
                PostQuitMessage(0);
            }
        }
        break;

    case UIState::GAME_SETTINGS:
        setting->Update(diKeys);
        if (diKeys[DIK_ESCAPE] & 0x80) {
            SetState(UIState::MAIN_MENU);
            myAudioManager->setMusicVolume(setting->GetMusicVolume());
            myAudioManager->setSoundEffectsVolume(setting->GetSoundVolume());
        }
        break;
    
    }
}

void GameUI::Render() {
    switch (currentState) {
    case UIState::MAIN_MENU:
        mainMenu->Render();
        break;
    case UIState::GAME_SETTINGS:
        mainMenu->Render(); //render main menu for background
        setting->Render();  // render setting pop out
        break;
    }
}

void GameUI::SetState(UIState newState) {
    currentState = newState;
    OutputDebugStringA("UI State changed\n");
}