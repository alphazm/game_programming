#include "AudioManager.h"

void AudioManager::initialize() {
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	system->createChannelGroup("Music", &musicChannelGroup);
	system->createChannelGroup("SFX", &sfxChannelGroup);
	musicVolume = 1.0f;  // Start at maximum volume
	soundEffectsVolume = 1.0f;  // Start at maximum volume
	musicChannel = nullptr;
	sfxChannel = nullptr;
	isMusicPlaying = false;
}
void AudioManager::setMusicVolume(float volume) {
	musicVolume = volume;
	if (musicChannel) {
		musicChannel->setVolume(volume);
	}
}

void AudioManager::setSoundEffectsVolume(float volume) {
	soundEffectsVolume = volume;
	sfxChannelGroup->setVolume(volume);
}
void AudioManager::playSound()
{
	result = system->playSound(sound1, sfxChannelGroup, false, &channel);
	channel->setVolume(1.0f);
	
}

void AudioManager::playSound3() {
	result = system->playSound(sound3, sfxChannelGroup, false, &sfxChannel);
	if (sfxChannel) {
		sfxChannel->setVolume(soundEffectsVolume);
	}
}

void AudioManager::stopMusic() {
	if (musicChannel) {
		musicChannel->stop();
		musicChannel = nullptr;
		isMusicPlaying = false;
	}
}

void AudioManager::stopSoundEffects() {
	if (sfxChannel) {
		sfxChannel->stop();
		sfxChannel = nullptr;
	}
}

void AudioManager::playSoundTrack() {
	if (!isMusicPlaying) {
		stopMusic();
		result = system->playSound(sound2, musicChannelGroup, false, &musicChannel);
		if (musicChannel) {
			musicChannel->setVolume(musicVolume);
			musicChannel->setMode(FMOD_LOOP_NORMAL);  
			isMusicPlaying = true;
		}
	}
	else {
		if (musicChannel) {
			musicChannel->setVolume(musicVolume);
		}
	}
}

void AudioManager::loadSounds()
{
	result = system->createSound("assets/gunshot",FMOD_DEFAULT,0,&sound1);
	result = sound1->setMode(FMOD_LOOP_OFF);

	result = system->createStream("assets/bgm.wav", FMOD_DEFAULT, 0, &sound2);
	result = sound2->setMode(FMOD_LOOP_OFF);

	result = system->createStream("assets/click.wav", FMOD_DEFAULT, 0, &sound3);
	result = sound3->setMode(FMOD_LOOP_OFF);
}
void AudioManager::toggleMusicPause() {
	if (musicChannel) {
		bool paused;
		musicChannel->getPaused(&paused);
		musicChannel->setPaused(!paused);
	}
}

void AudioManager::updateSound()
{
	result = system->update();
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	stopMusic();
	stopSoundEffects();
}
