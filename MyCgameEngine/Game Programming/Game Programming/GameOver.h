#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "State.h"

class GameOver : public State {
private:
    IDirect3DDevice9* device;
    ID3DXSprite* sprite;
    ID3DXFont* font;
    int winningPlayer;
    LPDIRECT3DTEXTURE9 popupTexture;
    float scaleX = 0.5f;
    float scaleY = 0.5f;
    D3DXMATRIX scaleMatrix;
    D3DXMATRIX identityMatrix;

    int selectedOption;
    const int totalOptions = 3; 

public:
    GameOver(IDirect3DDevice9* dev);
    ~GameOver();

    void Initialize();
    void update() override;
    void draw() override;
    void init() override;
    void release() override;
    void SetWinningPlayer(int player);
    bool CheckForRestart();
};