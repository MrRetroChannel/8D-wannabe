#pragma once
#include <AL/alc.h>
class SoundDevice
{
	SoundDevice();
	~SoundDevice();
	ALCdevice* device;
	ALCcontext* context;
public:
	static SoundDevice* get();
};