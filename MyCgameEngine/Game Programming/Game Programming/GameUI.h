#pragma once
#include <d3d9.h>
#include "MainMenu.h"
#include "AudioManager.h"
#include "Setting.h"

enum class UIState { MAIN_MENU, GAME_SETTINGS, IN_GAME, PAUSE_MENU };

class GameUI {
private:
    IDirect3DDevice9* d3dDevice;
    UIState currentState;
    MainMenu* mainMenu;
    Setting* setting;
    AudioManager* sounds;
    AudioManager* myAudioManager = new AudioManager();


public:
    GameUI(IDirect3DDevice9* device);
    ~GameUI();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    void SetState(UIState newState);
    UIState GetState() const { return currentState; }
};