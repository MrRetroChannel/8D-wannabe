#include "SoundDevice.h"
#include <AL/al.h>
#include <iostream>

SoundDevice* SoundDevice::get()
{
	static SoundDevice* a = new SoundDevice;
	return a;
}

SoundDevice::SoundDevice()
{
	device = alcOpenDevice(nullptr);
	
	context = alcCreateContext(device, nullptr);

	if (!alcMakeContextCurrent(context))
		std::cout << "blin";
}

SoundDevice::~SoundDevice()
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}