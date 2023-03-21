#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "AudioFile/AudioFile.h"

#include "UVec3.h"

#include <iostream>
/*
	I went with OpenAL simply because it was the first library that I knew dealt with music,
	and I found a very good tutorial on how to implement it into my project
*/
class AudioSub
{
public:

	//These variables are for the setup
	ALCdevice* device;
	ALCcontext* context;

	//For the sound itself, I only used stereo sound
	ALuint stereoSoundBuffer;
	ALint sourceState;
	ALuint stereoSource;

	//This variable changes based on a keypress, and allows for the sound to start or stop
	static bool listening;

	AudioSub();
	~AudioSub();

	void AudioInitialise();

	static void AudioUpdate(UVec3 vec3);

	void ImportStereoSound();

	static void SetListening(bool play);

	void PlayPlayerSound();
};

