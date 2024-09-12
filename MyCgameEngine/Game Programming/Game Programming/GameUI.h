#pragma once
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

enum class UIState {
    MAIN_MENU,
    GAME_SETTINGS,
    IN_GAME,
    PAUSE_MENU
};

struct MenuItem {
    std::string text;
    D3DXVECTOR2 position;
    bool isSelected;
};

class GameUI {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    UIState currentState;
    std::vector<MenuItem> menuItems;
    int selectedItemIndex;

public:
    GameUI(IDirect3DDevice9* device);
    ~GameUI();

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    int GetSelectedItemIndex() const { return selectedItemIndex; }
    void SetState(UIState newState);
    UIState GetState() const { return currentState; }

private:
    void RenderMainMenu();
    void RenderGameSettings();
    void RenderInGame();
    void RenderPauseMenu();
};
