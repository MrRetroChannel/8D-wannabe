#pragma once
#include <AL/al.h>
class SoundSrc
{
	ALuint source, buffer = 0, channels=0;
	float pitch = 2.0f, gain = 0.5f, position[3] = { 0, 0, 0 }, velocity[3] = { 0, 0, 0 };
	bool loopSound = false;
public:
	void play(const ALuint src, int side);
	SoundSrc(int a);
	~SoundSrc();
};