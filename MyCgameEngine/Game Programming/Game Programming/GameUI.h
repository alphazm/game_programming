#pragma once
#include <d3d9.h>
#include "MainMenu.h"
#include "AudioManager.h"
#include "Setting.h"
#include "PauseMenu.h"

enum class UIState {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_SETTINGS = 2,
    PAUSE_MENU = 3
};
class GameUI {
private:
    IDirect3DDevice9* d3dDevice;
    UIState currentState;
    MainMenu* mainMenu;
    Setting* setting;
    AudioManager* sounds;
    PauseMenu* pauseMenu;
    AudioManager* myAudioManager = new AudioManager();
    UIState previousState;

public:
    GameUI(IDirect3DDevice9* device);
    ~GameUI();
    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    void SetState(UIState newState);
    UIState GetState() const { return currentState; }
};