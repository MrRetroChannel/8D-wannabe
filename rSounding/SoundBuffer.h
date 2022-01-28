#pragma once
#include <AL/al.h>
#include <vector>
#include <sndfile.h>
class SoundBuffer
{
	std::vector<ALuint> soundbuf;
	SoundBuffer();
	~SoundBuffer();
public:
	static SoundBuffer* get();
	ALuint AddSoundEffect(const char* file);
	bool removeSoundEffect(const ALuint& buf);
};
