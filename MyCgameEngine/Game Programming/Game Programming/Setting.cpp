#include "Setting.h"
#include <dinput.h>
#include <sstream>

Setting::Setting(IDirect3DDevice9* device, AudioManager* audio): d3dDevice(device), audioManager(audio) {
    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create sprite\n");
    }

    hr = D3DXCreateFont(d3dDevice, 40, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New", &font);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create font\n");
    }
    musicVolume = audioManager->getMusicVolume();
    soundVolume = audioManager->getSoundEffectsVolume();
    musicVolume = 1.0f;  // Start at maximum volume
    soundVolume = 1.0f;  // Start at maximum volume
    audioManager->setMusicVolume(musicVolume);
    audioManager->setSoundEffectsVolume(soundVolume);
}

Setting::~Setting() {
    if (sprite) sprite->Release();
    if (font) font->Release();
}

void Setting::Initialize() {
}

void Setting::Update(const BYTE* diKeys) {
    bool volumeChanged = false;
    if (diKeys[DIK_UP] & 0x80) {
        musicVolume = min(musicVolume + 0.01f, 1.0f);
        volumeChanged = true;
    }
    if (diKeys[DIK_DOWN] & 0x80) {
        musicVolume = max(musicVolume - 0.01f, 0.0f);
        volumeChanged = true;
    }
    if (diKeys[DIK_RIGHT] & 0x80) {
        soundVolume = min(soundVolume + 0.01f, 1.0f);
        volumeChanged = true;
    }
    if (diKeys[DIK_LEFT] & 0x80) {
        soundVolume = max(soundVolume - 0.01f, 0.0f);
        volumeChanged = true;
    }

    if (volumeChanged) {
        audioManager->setMusicVolume(musicVolume);
        audioManager->setSoundEffectsVolume(soundVolume);
        audioManager->playSound3();  
    }
}

void Setting::Render() {
    d3dDevice->BeginScene();
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    
    D3DXVECTOR3 pos(200, 100, 0);
    RECT windowRect = { 0, 0, 500, 300 };
    D3DCOLOR bgColor = D3DCOLOR_ARGB(200, 0, 0, 0);  
    sprite->Draw(NULL, &windowRect, NULL, &pos, bgColor);

    // Render volume settings
    RECT textRect = { 220, 120, 0, 0 };
    std::ostringstream musicStream;
    musicStream << "Music Volume: " << static_cast<int>(musicVolume * 100) << "%";
    font->DrawText(sprite, musicStream.str().c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

    textRect.top += 50;
    std::ostringstream soundStream;
    soundStream << "Sound Effects Volume: " << static_cast<int>(soundVolume * 100) << "%";
    font->DrawText(sprite, soundStream.str().c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

    DrawVolumeBar(250, 160, musicVolume, D3DCOLOR_XRGB(0, 255, 0)); 
    DrawVolumeBar(250, 210, soundVolume, D3DCOLOR_XRGB(255, 255, 0)); 

    textRect.top += 100;
    font->DrawText(sprite, "Press ESC to return to Main Menu", -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

    sprite->End();
    d3dDevice->EndScene();
}

void Setting::DrawVolumeBar(int x, int y, float volume, D3DCOLOR color) {
    RECT barRect = { x, y, x + static_cast<int>(volume * 200), y + 20 };
    sprite->Draw(NULL, &barRect, NULL, NULL, color);
}