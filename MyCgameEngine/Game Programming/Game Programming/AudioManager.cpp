#include "AudioManager.h"

void AudioManager::initialize()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL,extradriverdata);
}

void AudioManager::playSound()
{
	result = system->playSound(sound1, 0, false, &channel);
}

void AudioManager::playSoundTrack()
{
	result = system->playSound(sound2, 0, true, &channel);
	channel->setPan(0);
	channel->setVolume(0.8);
	channel->setPaused(false);
}

void AudioManager::loadSounds()
{
	result = system->createSound("assets/gunshot",FMOD_DEFAULT,0,&sound1);
	result = sound1->setMode(FMOD_LOOP_OFF);

	result = system->createStream("", FMOD_DEFAULT, 0, &sound2);
	result = sound2->setMode(FMOD_LOOP_OFF);
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
}
