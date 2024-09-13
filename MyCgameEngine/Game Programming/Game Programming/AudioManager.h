#pragma once
#include "fmod.hpp"
class AudioManager
{
private:
	FMOD::System *system;
	FMOD::Sound* sound1, * sound2, * sound3;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;

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
	void playSoundTrack();
	void loadSounds();
	void updateSound();
	void setMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	void stopMusic();
	void stopSoundEffects();
	float getMusicVolume() const { return musicVolume; }
	float getSoundEffectsVolume() const { return soundEffectsVolume; }
	void toggleMusicPause();
	AudioManager();
	~AudioManager();
};

