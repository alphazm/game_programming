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
public:
	void initialize();
	void playSound();
	void playSound3();
	void playSoundTrack();
	void loadSounds();
	void updateSound();
	
	AudioManager();
	~AudioManager();
};

