#include "Setting.h"
#include <dinput.h>
#include <sstream>

Setting::Setting(IDirect3DDevice9* device, AudioManager* audio) : d3dDevice(device), audioManager(audio) {
    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create sprite\n");
    }

    hr = D3DXCreateFont(d3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New", &smallFont);

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
    if (popupTexture) popupTexture->Release();
    if (font) font->Release();
}

void Setting::Initialize() {
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "assets/Window.png", &popupTexture);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to load popup texture\n");
    }
}

void Setting::Update(const BYTE* diKeys) {
    bool volumeChanged = false;
    bool musicVolumeChanged = false;
    bool soundVolumeChanged = false;
    if (diKeys[DIK_UP] & 0x80) {
        musicVolume = min(musicVolume + 0.01f, 1.0f);
        volumeChanged = true;
        musicVolumeChanged = true;
    }
    if (diKeys[DIK_DOWN] & 0x80) {
        musicVolume = max(musicVolume - 0.01f, 0.0f);
        volumeChanged = true;
        musicVolumeChanged = true;
    }
    if (diKeys[DIK_RIGHT] & 0x80) {
        soundVolume = min(soundVolume + 0.01f, 1.0f);
        volumeChanged = true;
        soundVolumeChanged = true;
    }
    if (diKeys[DIK_LEFT] & 0x80) {
        soundVolume = max(soundVolume - 0.01f, 0.0f);
        volumeChanged = true;
        soundVolumeChanged = true;
    }

    if (volumeChanged) {
        audioManager->setMusicVolume(musicVolume);
        audioManager->setSoundEffectsVolume(soundVolume);
    }

    if (soundVolumeChanged) {
        audioManager->playSound3();
    }
}

void Setting::Render() {
    //d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    /*d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);*/

    if (popupTexture) {
        D3DXVECTOR3 pos(400, 200, 0);
        RECT windowRect = { 0, 0, 940, 800 };

        
        D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1.0f);
        sprite->SetTransform(&scaleMatrix);

        sprite->Draw(popupTexture, &windowRect, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255, 255));

        D3DXMatrixIdentity(&identityMatrix);
        sprite->SetTransform(&identityMatrix);
    }
    d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    RECT titleRect = { 220, 110, 0, 0 };
    font->DrawText(sprite, "Settings", -1, &titleRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));

    // Render volume settings
    RECT textRect = { 220, 180, 0, 0 };
    std::ostringstream musicStream;
    musicStream << "Music Volume: " << static_cast<int>(musicVolume * 100) << "%";
    font->DrawText(sprite, musicStream.str().c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));

    RECT reminderRect = { 220, 220, 0, 0 };
    std::ostringstream reminder1;
    reminder1 << "note: Use left/right arrow to control";
    smallFont->DrawText(sprite, reminder1.str().c_str(), -1, &reminderRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));

    textRect.top += 100;
    std::ostringstream soundStream;
    soundStream << "Sound Volume: " << static_cast<int>(soundVolume * 100) << "%";
    font->DrawText(sprite, soundStream.str().c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));

    RECT reminderRect2 = { 220, 320, 0, 0 };
    std::ostringstream reminder2;
    reminder2 << "note: Use up/down arrow to control";
    smallFont->DrawText(sprite, reminder2.str().c_str(), -1, &reminderRect2, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));


    textRect.top += 150;
    font->DrawText(sprite, "Press ESC to exit", -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255, 255));

    sprite->End();
    d3dDevice->EndScene();
}