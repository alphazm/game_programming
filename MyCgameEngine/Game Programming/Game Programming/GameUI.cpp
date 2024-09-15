#include "GameUI.h"
#include <dinput.h>

GameUI::GameUI(IDirect3DDevice9* device) : d3dDevice(device), currentState(UIState::MAIN_MENU) {
    myAudioManager = new AudioManager();
    mainMenu = new MainMenu(device);
    setting = new Setting(device, myAudioManager);
    pauseMenu = new PauseMenu(device);
}

GameUI::~GameUI() {
    delete mainMenu;
    delete setting;
    delete myAudioManager;
    delete pauseMenu;
}

void GameUI::Initialize() {
    myAudioManager->initialize();
    myAudioManager->loadSounds();
    myAudioManager->playSoundTrack();
    mainMenu->Initialize();
    setting->Initialize();
    pauseMenu->Initialize();
}

void GameUI::Update(const BYTE* diKeys) {
    static bool pKeyPressed = false;
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
    case UIState::IN_GAME:
        if (diKeys[DIK_P] & 0x80 && !pKeyPressed) {
            myAudioManager->playSound4();
            SetState(UIState::PAUSE_MENU);
            pKeyPressed = true;
        }
        else if (!(diKeys[DIK_P] & 0x80)) {
            pKeyPressed = false;
        }
        break;

    case UIState::PAUSE_MENU:
        pauseMenu->Update(diKeys);
        if (diKeys[DIK_RETURN] & 0x80) {
            myAudioManager->playSound3(); 
            int selectedIndex = pauseMenu->GetSelectedIndex();
            switch (selectedIndex) {
            case 0:
                SetState(UIState::IN_GAME);
                break;
            case 1:
                SetState(UIState::IN_GAME);
                break;
            case 2:
                SetState(UIState::GAME_SETTINGS);
                break;
            case 3:
                SetState(UIState::MAIN_MENU);
                break;
            }
        }
        if (diKeys[DIK_ESCAPE] & 0x80) {
            SetState(UIState::IN_GAME);
        }
        break;

    case UIState::GAME_SETTINGS:
        setting->Update(diKeys);
        if (diKeys[DIK_ESCAPE] & 0x80) {
            if (previousState == UIState::PAUSE_MENU) {
                SetState(UIState::PAUSE_MENU);
            }
            else {
                SetState(UIState::MAIN_MENU);
            }
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
    case UIState::IN_GAME:

        break;
    case UIState::PAUSE_MENU:
        pauseMenu->Render();
        break;
    case UIState::GAME_SETTINGS:
        if (previousState == UIState::PAUSE_MENU) {
        }
        else {
            mainMenu->Render(); // render main menu for background
        }
        setting->Render();  // render setting pop out
        break;
    }
}

void GameUI::SetState(UIState newState) {
    previousState = currentState;
    currentState = newState;
    OutputDebugStringA("UI State changed\n");
}