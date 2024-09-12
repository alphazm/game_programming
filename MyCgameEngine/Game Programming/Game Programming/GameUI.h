#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

enum class UIState { MAIN_MENU, GAME_SETTINGS, IN_GAME, PAUSE_MENU };

class GameUI {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    UIState currentState;
    std::vector<std::string> menuItems;
    int selectedItemIndex;

public:
    GameUI(IDirect3DDevice9* device);
    ~GameUI();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    void SetState(UIState newState);
    UIState GetState() const { return currentState; }
};
