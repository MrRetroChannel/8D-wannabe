#include <iostream>
#include <windows.h>
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSrc.h"
#include <thread>

int main()
{
	SoundDevice* dev = SoundDevice::get();
	uint32_t sound1 = SoundBuffer::get()->AddSoundEffect("1.ogg");
	SoundSrc speaker(-1), speaker1(1);
	std::thread A([&](){ speaker1.play(sound1, 1); });
	speaker.play(sound1, -1);
}