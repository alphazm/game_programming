#include "Lvl.h"
#include <dinput.h>

Lvl::Lvl(IDirect3DDevice9* device, AudioManager* audioManager)
    : d3dDevice(device), myAudioManager(audioManager) {
    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create sprite in Lvl\n");
    }
}

Lvl::~Lvl() {
    if (sprite) {
        sprite->Release();
    }
    if (backgroundTexture) {
        backgroundTexture->Release();
    }
}

void Lvl::Initialize() {
    myAudioManager->initialize();
    myAudioManager->loadSounds();
    myAudioManager->playSoundTrack2();
    myAudioManager->setMusicVolume(myAudioManager->getMusicVolume());
    myAudioManager->setSoundEffectsVolume(myAudioManager->getSoundEffectsVolume());
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "assets/bg3.jpg", &backgroundTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load in-game background texture\n");
    }
    
}

void Lvl::Update(const BYTE* diKeys) {
    if (diKeys[DIK_P] & 0x80) {
        myAudioManager->playSound4();
    }
}

void Lvl::Render() {
    if (backgroundTexture) {
        d3dDevice->BeginScene();
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        sprite->Begin(D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
        RECT destRect = { 0, 0, 960, 600 }; 
        sprite->Draw(backgroundTexture, &destRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
        sprite->End();

        d3dDevice->EndScene();
        d3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}
