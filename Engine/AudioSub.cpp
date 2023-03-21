#include "AudioSub.h"

/*
This code and the changes to the AudioFile.h code were taken from a YouTube video
Link: https://www.youtube.com/watch?v=WvND0djMcfE
*/

/*
The test sound can be found here
Link: https://www.youtube.com/watch?v=2ZIpFytCSVc
*/

//OpenAL error checking
#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if( error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
	}\
}

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)

bool AudioSub::listening;

AudioSub::AudioSub()
{
}

AudioSub::~AudioSub()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// clean up our resources!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alDeleteSources(1, &stereoSource));
	alec(alDeleteBuffers(1, &stereoSoundBuffer));
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioSub::AudioInitialise()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// find the default audio device
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const ALCchar* defaultDeviceString = alcGetString(/*device*/nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(defaultDeviceString);
	if (!device)
	{
		std::cerr << "failed to get the default device for OpenAL" << std::endl;
		return;
	}
	std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create an OpenAL audio context from the device
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	context = alcCreateContext(device, /*attrlist*/ nullptr);
	if (!alcMakeContextCurrent(context))
	{
		std::cerr << "failed to make the OpenAL context the current context" << std::endl;
		return;
	}

	ImportStereoSound();
}

void AudioSub::AudioUpdate(UVec3 vec3)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a listener in 3d space (ie the player); (there always exists as listener, you just configure data on it)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alListener3f(AL_POSITION, vec3.x, vec3.y, vec3.z));
	alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
	ALfloat forwardAndUpVectors[] = {
		/*forward = */ 1.f, 0.f, 0.f,
		/* up = */ 0.f, 1.f, 0.f
	};
	alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));
}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create buffers that hold our sound data; these are shared between contexts and ar defined at a device level
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	auto convertFileToOpenALFormat = [](const AudioFile<float>& audioFile) {
		int bitDepth = audioFile.getBitDepth();
		if (bitDepth == 16)
			return audioFile.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		else if (bitDepth == 8)
			return audioFile.isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		else
			return -1; // this shouldn't happen!
	};

void AudioSub::ImportStereoSound()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// load a stereo file into a buffer
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AudioFile<float> stereoSoundFile;
	if (!stereoSoundFile.load("audio/test.wav"))
	{
		std::cerr << "failed to load the test stereo sound file" << std::endl;
	}
	std::vector<uint8_t> stereoPCMDataBytes;
	stereoSoundFile.writePCMToBuffer(stereoPCMDataBytes); //remember, we added this function to the AudioFile library

	alec(alGenBuffers(1, &stereoSoundBuffer));
	alec(alBufferData(stereoSoundBuffer, convertFileToOpenALFormat(stereoSoundFile), stereoPCMDataBytes.data(), stereoPCMDataBytes.size(), stereoSoundFile.getSampleRate()));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// create a sound source for our stereo sound; note 3d positioning doesn't work with stereo files because
	// stereo files are typically used for music. stereo files come out of both ears so it is hard to know
	// what the sound should be doing based on 3d position data.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alGenSources(1, &stereoSource));
	alec(alSource3f(stereoSource, AL_POSITION, 0.f, 0.f, 1.f)); //NOTE: this does not work like mono sound positions!
	alec(alSource3f(stereoSource, AL_VELOCITY, 0.f, 0.f, 0.f)); 
	alec(alSourcef(stereoSource, AL_PITCH, 1.f));
	alec(alSourcef(stereoSource, AL_GAIN, 1.f));
	alec(alSourcei(stereoSource, AL_LOOPING, AL_TRUE));
	alec(alSourcei(stereoSource, AL_BUFFER, stereoSoundBuffer));

	/*alec(alSourcePlay(stereoSource));
	alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));*/
	if (sourceState == AL_PLAYING)
	{
		//basically loop until we're done playing the mono sound source
		alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
	}

	alec(alSourcePause(stereoSource));
}

//This is where we set the listening variable on or off
void AudioSub::SetListening(bool play)
{
	if (play)
	{
		listening = true;
	}
	else
	{
		listening = false;
	}
}

void AudioSub::PlayPlayerSound()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// play the stereo sound source based on a keypress.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (listening)
	{
		alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
		if (sourceState != AL_PLAYING)
		{
			alec(alSourcePlay(stereoSource));
		}
	}
	else
	{
		alec(alSourcePause(stereoSource));
	}
}

