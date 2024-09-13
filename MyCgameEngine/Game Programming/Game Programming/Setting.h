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
    float musicVolume;
    float soundVolume;
    AudioManager* audioManager;
public:
    Setting(IDirect3DDevice9* device);
    ~Setting();
    Setting(IDirect3DDevice9* device, AudioManager* audio);

    void Initialize();
    void Update(const BYTE* diKeys);
    void Render();
    void DrawVolumeBar(int x, int y, float volume, D3DCOLOR color);
    void SetMusicVolume(float volume) { musicVolume = volume; }
    void SetSoundVolume(float volume) { soundVolume = volume; }
    float GetMusicVolume() const { return musicVolume; }
    float GetSoundVolume() const { return soundVolume; }
};