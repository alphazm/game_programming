#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include "AudioManager.h"


class Setting {
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPD3DXFONT smallFont; 
    float musicVolume;
    float soundVolume;
    AudioManager* audioManager;
    LPDIRECT3DTEXTURE9 popupTexture;
    bool volumeChanged = false;
    bool musicVolumeChanged = false;
    bool soundVolumeChanged = false;
    float scaleX = 0.5f;
    float scaleY = 0.5f;
public:
    Setting(IDirect3DDevice9* device);
    ~Setting();
    Setting(IDirect3DDevice9* device, AudioManager* audio);
    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    void SetMusicVolume(float volume) { musicVolume = volume; }
    void SetSoundVolume(float volume) { soundVolume = volume; }
    float GetMusicVolume() const { return musicVolume; }
    float GetSoundVolume() const { return soundVolume; }
};