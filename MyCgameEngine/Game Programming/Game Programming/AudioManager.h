#pragma once
#include "fmod.hpp"
class AudioManager
{
private:
	FMOD::System *system;
	FMOD::Sound* sound1, * sound2, * sound3, * sound4, * sound5;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;
	float soundtrackVolumeScale;
	float musicVolume;
	float soundEffectsVolume;
	FMOD::ChannelGroup* musicChannelGroup;
	FMOD::ChannelGroup* sfxChannelGroup;
	FMOD::Channel* musicChannel;
	FMOD::Channel* sfxChannel;

	bool isMusicPlaying;

public:
	void initialize();
	void playSound();
	void playSound3();
	void playSound4();
	void playSoundTrack();
	void playSoundTrack2();
	void loadSounds();
	void updateSound();
	void setMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	float getMusicVolume() const { return musicVolume; }
	float getSoundEffectsVolume() const { return soundEffectsVolume; }
	void stopMusic();
	void stopSoundEffects();
	void toggleMusicPause();
	AudioManager();
	~AudioManager();
};

