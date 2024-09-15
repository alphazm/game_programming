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
    delete level;
}

void GameUI::Initialize() {
    myAudioManager->initialize();
    myAudioManager->loadSounds();
    myAudioManager->playSoundTrack();
    mainMenu->Initialize();
    setting->Initialize();
    pauseMenu->Initialize();
    //need to move this
    
}

void GameUI::Update(const BYTE* diKeys) {
    static bool returnKeyPressed = false; // Debounce for return key
    static bool pKeyPressed = false;

    switch (currentState) {
    case UIState::MAIN_MENU:
        mainMenu->Update(diKeys);
        if (diKeys[DIK_RETURN] & 0x80) {
            if (!returnKeyPressed) { // Only process if not already pressed
                returnKeyPressed = true;
                myAudioManager->playSound3();
                int selectedIndex = mainMenu->GetSelectedIndex();

                if (selectedIndex == 0) {
                    myAudioManager->stopMusic();
                    level = new Lvl(d3dDevice, myAudioManager);
                    level->Initialize();
                    /*myAudioManager->setMusicVolume(setting->GetMusicVolume()); 
                    myAudioManager->setSoundEffectsVolume(setting->GetSoundVolume());*/
                    SetState(UIState::IN_GAME);
                }
                else if (selectedIndex == 1) {
                    SetState(UIState::GAME_SETTINGS);
                    /*setting->SetMusicVolume(1.0f);
                    setting->SetSoundVolume(1.0f);
                    myAudioManager->setMusicVolume(1.0f);
                    myAudioManager->setSoundEffectsVolume(1.0f);*/
                }
                else if (selectedIndex == 2) {
                    PostQuitMessage(0);
                }
            }
        }
        else {
            returnKeyPressed = false; // Reset when key is released
        }
        break;

    case UIState::IN_GAME:
        if (level) {
            level->Update(diKeys);
        }
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
            if (!returnKeyPressed) { // Only process if not already pressed
                returnKeyPressed = true;
                myAudioManager->playSound3();
                int selectedIndex = pauseMenu->GetSelectedIndex();
                switch (selectedIndex) {
                case 0: // Resume
                    SetState(UIState::IN_GAME);
                    break;
                case 1: // Restart
                    SetState(UIState::IN_GAME);
                    break;
                case 2: // Settings
                    SetState(UIState::GAME_SETTINGS);
                    break;
                case 3: // Main Menu
                    myAudioManager->stopMusic();
                    delete level;
                    level = nullptr;
                    myAudioManager->playSoundTrack();
                    SetState(UIState::MAIN_MENU);
                    break;
                default:
                    char debugMsg[100];
                    sprintf_s(debugMsg, "Unexpected pause menu index: %d\n", selectedIndex);
                    OutputDebugStringA(debugMsg);
                    break;
                }
            }
        }
        else {
            returnKeyPressed = false; // Reset when key is released
        }
        if (diKeys[DIK_ESCAPE] & 0x80) {
            myAudioManager->playSound4();
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
        if (level) {
            level->Render(); 
        }
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
        /*d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
        setting->Render();  // render setting pop out
        break;
    }
}

void GameUI::SetState(UIState newState) {
    previousState = currentState;
    currentState = newState;

    /*if (currentState == UIState::GAME_SETTINGS) {
        setting->SetMusicVolume(myAudioManager->getMusicVolume());
        setting->SetSoundVolume(myAudioManager->getSoundEffectsVolume());
    }*/
    char debugMsg[100];
    sprintf_s(debugMsg, "UI State changed from %d to %d\n", static_cast<int>(previousState), static_cast<int>(currentState));
    OutputDebugStringA(debugMsg);

    // Additional debugging
    switch (currentState) {
    case UIState::MAIN_MENU:
        OutputDebugStringA("Entered MAIN_MENU state\n");
        break;
    case UIState::IN_GAME:
        OutputDebugStringA("Entered IN_GAME state\n");
        break;
    case UIState::PAUSE_MENU:
        OutputDebugStringA("Entered PAUSE_MENU state\n");
        break;
    case UIState::GAME_SETTINGS:
        OutputDebugStringA("Entered GAME_SETTINGS state\n");
        break;
    }
}