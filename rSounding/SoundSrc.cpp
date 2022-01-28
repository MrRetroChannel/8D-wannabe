#include "SoundSrc.h"
#include <iostream>
#include <cmath>

SoundSrc::SoundSrc(int a)
{
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, pitch);
	alSourcef(source, AL_GAIN, gain);
	alSource3f(source, AL_POSITION, a, position[1], position[2]);
	alSource3f(source, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
	alSourcei(source, AL_LOOPING, loopSound);
	alSourcei(source, AL_BUFFER, buffer);

}

enum side
{
	LEFT = -1,
	RIGHT = 1
};

void SoundSrc::play(const ALuint src, int side)
{
	if (src != buffer)
	{
		buffer = src;
		alSourcei(source, AL_BUFFER, (ALint)buffer);
	}
	alSourcePlay(source);
	ALint state = AL_PLAYING;
	double q = 0.000001 * side;
	float gn = gain;
	while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		alSourcef(source, AL_GAIN, gn);
		gn += q;
		if (gn >= 1.0 || gn <= 0.1)
			q *= -1;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
	}
}

SoundSrc::~SoundSrc()
{
	alDeleteSources(1, &source);
}

